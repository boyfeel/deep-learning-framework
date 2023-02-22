#pragma once

#include "../api/vcommon.h"
#include "../api_objects/vsession.h"
#include "../local_objects/vtensordata.h"
#include "../api_objects/vmodule.h"
#include "../local_objects/vcbbackinfo.h"

class VTensorCore : public VObjCore {
protected:
    friend class VTensor;
protected:
    VTensorCore(VSession session, string sBuiltin = "", VDict kwArgs = {});
    VTensorCore* clone() { return (VTensorCore*)clone_core(); }
    ~VTensorCore();
    void m_onCreate();
    void m_onDelete();
    VSession session() { return m_session; }
protected:
    VSession m_session;
    string m_sBuiltin;
    VDict m_propDict;
    int m_nCheckCode;
    static int ms_nCheckCode;

protected:
    VTensorCore();

    VShape m_shape;
    VDataType m_dataType;

    VTensorData m_data;

    bool m_bNeedGrad;
    VGraphOpCode m_opCode;

    VTensorList m_operands;
    //VList m_children;

    // ��� ĸ�� ��ü�� ����� ���� ��� ��ȯ������ ���� �޸� ���� �߻��Ѵ�.
    VModuleCore* m_pOwningModule;

    //memo("�ʱ�ȭ ���� ������ ��� ���� ���� �����ϰ� �ϰ�.");

    VValue m_aux; // ���� ������ �ʿ��� shape, list ���� ���� ������ �� �ټ��� �̵� ������ ��� Ȱ���Ѵ�.
    VDict m_opArgs; // ���� ������ �ʿ��� shape, list ���� ���� ������ ��� ù��° ��� ��� �ټ�(operands[0])�� ��� Ȱ���Ѵ�.
    VDict m_myArgs; // ���� ������ �ʿ��� shape, list ���� ���� ������ ��� ��� ��� �ټ�(result)�� ��� Ȱ���Ѵ�.
    // ���� �غ� �߿� �����Ǵ� ���� ������ result�� �������̹Ƿ� �̹� �غ�� ���۷����� m_args�� ��� �����Ѵ�.
    // ������ �� ���� ���� ����� �� �� �̻��� �ټ� ��꿡 �ݺ� Ȱ��Ǵ� ���۷��� �ټ��� ��� ������ �߻���Ų��.
    // ���� ��� �Ŀ��� result�� ������ result ���� �ٸ� ������ �ǿ����ڰ� �� �� �����Ƿ� ������ ������ ��ġ�Ѵ�.
    VDict m_initArgs; // �ʱ�ȭ ����� ���� ������ ������ ó�� �߿� �ټ� ������ �ٽ� �ʱ�ȭ���Ѿ� �ϴ� ��쿡 Ȱ���Ѵ�.

    int m_nOperandRefCount;

    vector<VCbBackSlot> m_cbBackSlots;

    static bool ms_bNoDump;
    static mutex ms_grad_mutex;

    void m_initParam(TensorInitMethod init_op, float mean, float init_arg, bool adaptive);
    void m_copyDataFrom(VTensorCore* src, VExecTracer tracer);
    void m_resetCbBackSlot(int sid);
};
