#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;

	//positoin=============================
	// ワールド、ビュー、プロジェクション行列を掛け合わせて座標変換を行う
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
    output.pos = mul(input.pos, wvp);
	
	//color=============================
	// 法線ベクトルの変換と正規化を行う
	// 入力された法線をワールド空間に変換し、正規化する
	float4 normal = float4(input.nrm.xyz, 0.0);				// 入力法線をfloat4に変換(w=0)
	float4 worldNormal = mul(normal, World);				// 法線をワールド座標に変換
	worldNormal = normalize(worldNormal);					// 法線ベクトルを正規化

	// 光源方向と法線ベクトルの内積を計算して拡散光を求める
	float d = -dot(Light.Direction.xyz, worldNormal.xyz);	// 光の方向と内積を計算
	
	d = saturate(d);		// dの値を0から1にクランプ

    output.col.xyz = input.col.xyz * d * Light.Diffuse.xyz;	// 拡散光の影響を乗算
    output.col.xyz += input.col.xyz * Light.Ambient.xyz;	// アンビエント光を加算
	output.col.xyz += Material.Emission.xyz;				// Emissionを加算
    output.col.a = input.col.a * Material.Diffuse.a;		// アルファ値
	
	//texture=============================
	// テクスチャ座標はそのまま使用
    output.tex = input.tex;
	
    return output;
}

