#pragma once

#include "../api/vcommon.h"
#include "../api_objects/vsession.h"
#include "../api_objects/vmodule.h"
#include "../api_objects/voptimizer.h"
#include "../local_objects/vgraph_node.h"
#include "../local_objects/vexectracer.h"
#include "../local_objects/vdevicemanager.h"
#include "../local_objects/vcbbackinfo.h"

class VGraphCore : public VObjCore {
protected:
    friend class VGraph;
protected:
    VGraphCore(VSession session, string sBuiltin = "", VDict kwArgs = {});
    VGraphCore* clone() { return (VGraphCore*)clone_core(); }
    VSession session() { return m_session; }
    void m_setup();
protected:
    VSession m_session;
    string m_sBuiltin;
    VDict m_propDict;

protected:
    friend class VGraphNode;

    VGraphNode m_rootNode;
    //VModuleCore* m_pModuleCore;

    VDeviceManager m_deviceMan;
    VOptimizer m_pOptimizer;

    int m_nTouchVersion;

    string m_sNetName;
    //VModuleCore* m_pNetModuleCore;

    VTensorDict m_xs;
    VTensorDict m_ys;

    bool m_train;
    bool m_noGrad;

    int m_device;

    VTensorDict m_sideTerms; // concat ���̾� ��� ���� ������ ���ٵǴ� �߰��� �ټ� ������ ��Ÿ���µ� �����

    VTensorDict* m_pCustomTerms; // custom loss ���� ó������ �����
    VGraphDict m_graphs; // custom loss ���� ó������ �����

    bool m_pmAllocaed;  // ��� �Ķ���Ͱ� ���� �޸� �Ҵ��� �޾Ҵ��� ������ �����ֱ� ���� ���� ���������� ��Ÿ��

    static int ms_nNextTouchVersion;

public:
    VTensor seekInput(string varName);  // Module���� ���̾� ó���� ���� �ϴ� ��쿡 ���� ����
    VTensor optimizerPreproc(VTensor param, VDict pmset, VExecTracer tracer);
    bool isParamAllocated() { return m_pmAllocaed; }

protected:
    VTensor m_seekTerm(string varName, VCbBackInfo cbInfo, VExecTracer tracer);

    void m_keepOutput(string varName, VTensor tensor);

};
