#pragma once

#include "../api/vcommon.h"
#include "../api_objects/vsession.h"

class VCbItemCore : public VObjCore {
protected:
	friend class VCbItem;
protected:
	VCbItemCore(VSession session, string sBuiltin = "", VDict kwArgs = {});
	VCbItemCore* clone() { return (VCbItemCore*)clone_core(); }
	VSession session() { return m_session; }
	void m_setup();
protected:
	VSession m_session;
	string m_sBuiltin;
	VDict m_propDict;

protected: // ���� �ʵ�
	void* m_pCbFunc;
	void* m_pCbClose;
	VDict m_instInfo;

protected:	// �ݹ� ���� ��� ����
	friend class VCbBackSlotCore;

	VDict m_filters;

protected:	// �ݹ� ȣ�� ��� ����
	VDict m_statusInfo;
	VDict m_tensorDict;
	VDict m_gradDict;

};
