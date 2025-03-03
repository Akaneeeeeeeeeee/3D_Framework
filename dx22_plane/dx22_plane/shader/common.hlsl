cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}

struct VS_IN
{
    float4 pos : POSITION0;
	float4 nrm : NORMAL0;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 tex : TEXCOORD0;
};

struct LIGHT {
	bool Enable;		// �g�p���邩�ۂ�
	bool3 Dummy;		// PADDING
	float4 Direction;	// ����
	float4 Diffuse;		// �g�U���˗p�̌��̋���
	float4 Ambient;		// ���p�̌��̋���
};

cbuffer LightBuffer : register(b3)	// 3�Ԗڂ̃o�b�t�@�Ɍ������
{
	LIGHT Light;
};

struct MATERIAL {
	float4	Ambient;		// �A���r�G���g
	float4	Diffuse;		// �f�B�t���[�Y
	float4	Specular;		// �X�y�L����
	float4	Emission;		// �G�~�b�V����
	float	Shiness;		// �V���C�l�X
	bool	TextureEnable;	// �e�N�X�`���g�p�m�F�t���O
	bool2	Dummy;			// �A���C�������g����
};

cbuffer MaterialBuffer : register(b4) 
{
	MATERIAL Material;
}

// UV���W�ړ��s��
cbuffer MaterialBuffer : register(b5)
{
	matrix matrixTex;
}
