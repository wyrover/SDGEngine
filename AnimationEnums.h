#pragma once

namespace SDGEngine
{
	enum EWrapMode
	{
		Default, // ����Ʈ ������
		Once, // �ѹ� ���
		Loop, // �ݺ� �÷���
		PingPong, // �ѹ� ���� ����ǰ� �ٽ� �������� ��� ����
		ClampForever // �ѹ��� �÷��̵ǰ� ������ ��ǿ� �����ȴ�.
	};
}
