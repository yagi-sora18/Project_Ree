#pragma once
// : unsigned char ��unsigned char�^�����Ƃ�enum class��錾
//eNone���̗񋓎q��unsigned char�ō����
enum class eInputState : unsigned char
{
	eNone,
	ePress,
	eRelease,
	eHeld,
};