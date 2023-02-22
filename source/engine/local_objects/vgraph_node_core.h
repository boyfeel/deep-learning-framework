#pragma once

#include "../api/vcommon.h"
#include "../api_objects/vsession.h"
#include "../api_objects/vtensor.h"
#include "../local_objects/vgraph.h"
#include "../local_objects/vdevicemanager.h"
#include "../local_objects/vgraph_node.h"

class VGraphNodeCore : public VObjCore {
protected:
    friend class VGraphNode;
protected:
    VGraphNodeCore(VSession session, string sBuiltin = "", VDict kwArgs = {});
    VGraphNodeCore* clone() { return (VGraphNodeCore*)clone_core(); }
    VSession session() { return m_session; }
    void m_setup();
protected:
    VSession m_session;
    string m_sBuiltin;
    VDict m_propDict;

protected:
    VGraphOpCode m_opCode;

    VDeviceManager m_deviceMan;
    VGraphCore* m_pGraphCore;   // ��ü �����Ͱ� �ƴ� ��ü ��ü�� ����� �� ��� ��ȯ ������ ���� �޸� �ݳ��� ������

    string m_varName;

    VTensor m_pm;	// pm �������� ��쿡 ���� �Ķ���� �ټ� ����, ��� ����̽� �޸𸮿� ���纻 Ȯ��
    VTensor m_grad;	// pm �������� ��쿡 ���� 0�� ����̽��� ���� ��絵 �ټ� ����, ���� ��ŷ �ʼ�

    VDict m_nesterovPmSet; // nesterov ��Ƽ�������� ��� velocity ���� �̿��� ��ó�� ���� ����
    VDict m_pmSet; // rnn �迭 ���̾�� ������, ����� ���ο� ���� �޸� �����Ǵ� �Ķ���͵��� �ϰ� �����ϱ� ���ؼ��� ���

    VValue m_aux;	// shape, list ������ ���� ��� �ʿ��� Ÿ������ ��ȯ�� ���

    vector<VGraphNode> m_children;

    void m_setup(string sExp, VList params, int& pos);
    void m_setup(VGraphNodeCore* src_core);
    void m_seekOperands(string layerExp, VList params, int& pos);

    VDict m_pmsetToCurDevice(VCbBackInfo cbInfo, VExecTracer tracer);

    VGraphNode m_split_multi_operands(VGraphNodeCore* pSrc, VGraphOpCode opCode, vector<VGraphNode> children);

    static int ms_skipSpaces(string layerExp, int& pos);

};
