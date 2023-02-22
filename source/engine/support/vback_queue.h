#pragma once

#include "../api/vcommon.h"
#include "../api_objects/vtensor.h"
#include "../api_objects/vsession.h"
#include "../local_objects/vexectracer.h"

class VBackQueue {
public:
	VBackQueue(VSession session, VExecTracer tracer);
	~VBackQueue();

	// 1. node�� pm Ÿ���̸� �ٷ� backprop() ȣ���� ó���ϰ� ����
	// 2. node ��ȣ�� m_GradMap�� �ִ��� �˻��� ������ ����, ������ ���
	// 3. node�� --opndRef# �����ϰ� �� ���� 0 ���� ũ�� ó�� ����
	//    3-1. 0 �����̰� ���� ó�� �� �ǳ� �� ��� �ƴϸ� m_freeQueue ���
	//    3-2. ���� ó�� �� �ǳ� �� ���� m_crossStack ���
	// => �� �ǳ� �� ģ���� ������ ���� �޼ҵ带 �߰��� �и���

	void regist(VTensor node, VTensor grad);
	void pushCross(VTensor node, VTensor grad);

	// �ս� ��꿡�� ������ �� ������ �Ű�� ��� �ټ� ���.
	// �̵��� ó������ ������ų ��� ���� ��� ���ҿ� �ݿ����� �����鼭
	// ó�� ��� ���۷������ regist()���� ����� �� �Ǿ� �۾��� �߸� �ߴܵǴ� ���°� �߻���
	void registCrossNodes(VTensorDict nodes);

	// ������ ó���� ���ʿ��� �ټ� ���
	// �̵��� ó������ ������ų ��� ���� ��� ���ҿ� �ݿ����� �����鼭
	// ó�� ��� ���۷������ regist()���� ����� �� �Ǿ� �۾��� �߸� �ߴܵǴ� ���°� �߻���
	void registNoGrad(VTensor node);

	// m_freeQueue.size() == 0, m_crossStack.size() == 0�̸� true
	// �� �̶� m_GradMap.size() != 0�̸� ���� �߻�
	bool isEnd();

	// 1. m_freeQueue.size() == 0�̰� m_crossStack.size() == 0�̸� ���� �߻�
	//    1-1. m_crossStack.size() > 0�̸� ���� ����̽����� �ϰ� �� �ǳʱ�
	// 2. m_freeQueue ���θ� pop�� �۾� ������� ����
	// 3. m_GradMap���� �����Ǵ�  �׸� ã�� �������� ������ �׸� ����
	// 4. �۾���� �ټ��� ������ �Լ� ȣ��
	// 5. �۾���� ���۷���� �� no_grad �ƴ� ���� �۾� ���  ����� ����� �Բ� push() ȣ�� �ʼ�
	void step();

protected:
	void m_dump(string action);
	void m_execute_parallel_queues(VExecTracer tracer);

	static void ms_branchMain(void* aux);

protected:
	VSession m_session;

	int m_nInstanceId;

	VTensorList m_freeStack;
	VTensorList m_emptyStack;
	VTensorMap m_gradMap;

	map<int, int> m_RefCnt; // debugging�� �ӽ� ����

	VTensorList m_crossStack;	// �� �ǳ� �� ������: parallel ó�� ���� �� �ǳʿ�, ������ ���� ó�� ���� ���Ƽ� ������ ��
	VTensorMap m_crossedMap;

	string m_lastOpName;

	VExecTracer m_execTracer;

public:
	static bool ms_bQueueTrace;
	static int ms_nNextInstanceId;
};
