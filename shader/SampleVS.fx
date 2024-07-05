
//---------------------------------------------------------------------------------
//	���_�V�F�[�_�[
//---------------------------------------------------------------------------------

//	���_�V�F�[�_�[�ŏ������邽�߂Ɏ󂯎�����
struct VS_INPUT
{
    float4 LPos : POSITION; //	���[�J�����W
    float3 LNormal : NORMAL; //	���[�J���@��
    float4 Color : COLOR; //	�F
};

//	���_�V�F�[�_�[�̊֐��Ōv�Z�������ʂ��������
struct VS_OUTPUT
{
    float4 SPos : POSITION; //	��ʍ��W
    float4 Color : COLOR; //	�F
      
    // ����̓s�N�Z���V�F�[�_�[�Ń��[���h���W���g������
    // �Ȃ̂ŁA�n�����̒��Ƀ��[���h���W�����ėp�ɂ��܂�
    float WPos : TEXCOORD1;  // ���[���h���W
};

//	���[���h�ϊ��s��
float4x4 World : register(c94);
//	�r���[�ϊ��s��
float4x4 View : register(c6);
//	�v���W�F�N�V�����ϊ��s��
float4x4 Projection : register(c2);

//---------------------------------------------------------------------------------
//	�e���_�̌v�Z
//---------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT In)
{
	//	���C�g�̕���
    float3 LightDir = { 0.5f, -2.0f, 1.0f };
	//	����
    float4 Ambient = { 0.3f, 0.3f, 0.3f, 1.0f };

    VS_OUTPUT Out = (VS_OUTPUT) 0;

	//	���[�J�����W�����[���h���W�ɕϊ��i���[���h�ϊ��j
    float4 WPos = mul(In.LPos, World);
	//	���[���h���W���J�������W�ɕϊ��i�r���[�ϊ��j
    float4 CPos = mul(WPos, View);
	//	�J�������W����ʍ��W�ɕϊ��i�v���W�F�N�V�����ϊ��j
    Out.SPos = mul(CPos, Projection);

	//	���C�g�̌����̋t�����̃x�N�g���i���K���j
    float3 L = normalize(-LightDir);
	//	���[�J���@�������[���h�@����
    float3 N = normalize(mul(In.LNormal, (float3x3) World));
	//	�Q�̃x�N�g���i N, L �j���疾�邳�v�Z
    Out.Color = In.Color * max(Ambient, dot(N, L));

	// �F���������蕪���邽�߂ɒ��_�V�F�[�_�[�ł͂Ȃ��s�N�Z���V�F�[�_�[�ŐF��ς���

// ���[���h���W��X�̒l�����ă}�C�i�X�̕��������F��ς��Ă݂܂�
//if(WPos.x < 0.0f)
//{
   // �F��ς��Ă݂܂�
//   Out.Color.g = 1.0f;
//}
    
	// �s�N�Z���V�F�[�_�[�ɂ킽��p�̃��[���h���W
    Out.WPos = (float3)WPos;
    
	//	�v�Z�������ʂ̍��W�ƐF����ꂽ���̂�Ԃ��܂�
    return Out;
}
