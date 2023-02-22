#include "vexception.h"

VException::VException() {
	m_core = new VExceptionCore();
}

VException::VException(VExceptionCore* core) {
	m_core = core->clone();
}

VException::VException(const VException& src) {
	m_core = src.m_core->clone();
}

VException::VException(int nErrCode, string file, int line) {
	if (nErrCode == 0) return;

	m_core = new VExceptionCore();

	std::replace(file.begin(), file.end(), '\\', '/');

	m_core->m_nErrCode = nErrCode;
	m_core->m_msgStack.push_back(m_createMessage(nErrCode, file, line));
}

VException::VException(int nErrCode, string sParam, string file, int line) {
	m_core = new VExceptionCore();

	std::replace(file.begin(), file.end(), '\\', '/');

	m_core->m_nErrCode = nErrCode;
	m_core->m_msgStack.push_back(m_createMessage(nErrCode, file, line, sParam));
}

VException::VException(int nErrCode, string sParam1, string sParam2, string file, int line) {
	m_core = new VExceptionCore();

	std::replace(file.begin(), file.end(), '\\', '/');

	m_core->m_nErrCode = nErrCode;
	m_core->m_msgStack.push_back(m_createMessage(nErrCode, file, line, sParam1, sParam2));
}

VException::VException(int nErrCode, string sParam1, string sParam2, string sParam3, string file, int line) {
	m_core = new VExceptionCore();

	std::replace(file.begin(), file.end(), '\\', '/');

	m_core->m_nErrCode = nErrCode;
	m_core->m_msgStack.push_back(m_createMessage(nErrCode, file, line, sParam1, sParam2, sParam3));
}

VException::VException(int nErrCode, const VException& src, string file, int line) {
	std::replace(file.begin(), file.end(), '\\', '/');

	m_core = src.m_core->clone();
	m_core->m_msgStack.push_back(m_createMessage(nErrCode, file, line));
}

VException::VException(int nErrCode, const VException& src, string sParam1, string file, int line) {
	std::replace(file.begin(), file.end(), '\\', '/');

	m_core = src.m_core->clone();
	m_core->m_msgStack.push_back(m_createMessage(nErrCode, file, line, sParam1));
}

VException::~VException() {
	m_core->destroy();
}

VException& VException::operator =(const VException& src) {
	if (&src != this) m_core = src.m_core->clone();
	return *this;
}

VRetCode VException::GetErrorCode() {
	return m_core->m_nErrCode;
}

string VException::m_createMessage(int nErrCode, string file, int line, string sParam1, string sParam2, string sParam3) {
	char buffer[1024];

	const char* p1 = (sParam1.length() > 0) ? sParam1.c_str() : "";
	const char* p2 = (sParam2.length() > 0) ? sParam2.c_str() : "";
	const char* p3 = (sParam3.length() > 0) ? sParam3.c_str() : "";

	ms_createMessage(buffer, nErrCode, p1, p2, p3);

	snprintf(buffer + strlen(buffer), 1024 - strlen(buffer), " in %s:%d", file.c_str(), line);

	return (string)buffer;
}

VList VException::GetErrorMessageList() {
	if (m_core->m_nErrCode == 0) return VList();
	return m_core->m_msgStack;
}

VList VException::GetErrorMessageList(VRetCode nErrorCode) {
	return VList({ "Sorry, error message for static code is not implemented yet..." });
}

void VException::ms_createMessage(char *pBuf, int nErrCode, const char* p1, const char* p2, const char* p3) {
	switch (nErrCode) {
	case VERR_INTERNAL_LOGIC:
		snprintf(pBuf, 1024, "���������� ���� ����: %s", p1);
		break;
	case VERR_SHAPE_CONV2D:
		snprintf(pBuf, 1024, "�Է� ������ ä�μ��� Conv2D ���̾��� xchn ���� ���յ��� �ʽ��ϴ�.");
		break;
	case VERR_PARALLEL_EVALUATION:
		snprintf(pBuf, 1024, "���� ó�� �������� ���ܰ� �߻��Ͽ����ϴ�.");
		break;
	case VERR_MACRO_UNREGISTERED:
		snprintf(pBuf, 1024, "��ϵ��� ���� ��ũ�� �̸� %s��(��) ���Ǿ����ϴ�.", p1);
		break;
	case VERR_SHAPE_NOT_2D_DIMENSION:
		snprintf(pBuf, 1024, "�������� ������ %s ���� 2���� ������ �ƴմϴ�.", p1);
		break;
	case VERR_BAD_SHAPE_TENSOR:
		snprintf(pBuf, 1024, "%s() �Լ��� ���� �ټ��� ������ ó�� ������ ���յ��� �ʽ��ϴ�.", p1);
		break;
	case VERR_UNMATCHED_SHAPE_IN_CROSSENTROPY:
		snprintf(pBuf, 1024, "ũ�ν���Ʈ���� ������ ���� �� ������ ������ ó�� ������ ���յ��� �ʽ��ϴ�.");
		break;
	case VERR_BAD_PADDING_DIMENSION:
		snprintf(pBuf, 1024, "�е� �������� ������ ���� 4���� ������ �ƴմϴ�.");
		break;
	case VERR_BAD_PADDING_ARGUMENT:
		snprintf(pBuf, 1024, "�е� ������ �� �� ���� ������ %s ���� �����Ǿ����ϴ�.", p1);
		break;
	case VERR_UNKNOWN_PADDING_MODE:
		snprintf(pBuf, 1024, "�е� ��� ������ �� �� ���� ������ %s ���� �����Ǿ����ϴ�.", p1);
		break;
	case VERR_LAYER_EXEC_INSHAPE_MISMATCH:
		snprintf(pBuf, 1024, "%s ���̾� �Է� ������ %s�� �����Ǿ����� %s ������ �����Ͱ� �־������ϴ�.", p1, p2, p3);
		break;
	case VERR_LAYER_EXEC_OUTSHAPE_MISMATCH:
		snprintf(pBuf, 1024, "%s ���̾� ��� ������ %s�� �����Ǿ����� %s ������ �����Ͱ� �����Ǿ����ϴ�.", p1, p2, p3);
		break;
	case VERR_WILL_BE_IMPLEMENTED:
		snprintf(pBuf, 1024, "���� ���� ������ %s ����� ���Ǿ����ϴ�.", p1);
		break;
	case VERR_INDEXING_ON_NULL_SHAPE:
		snprintf(pBuf, 1024, "������ �������� ���� ���� ������ ���� ���� ������ �õ��Ǿ����ϴ�.");
		break;
	case VERR_HOSTMEM_ALLOC_FAILURE:
		snprintf(pBuf, 1024, "ȣ��Ʈ �޸� ����� �Ҵ翡 �����߽��ϴ�. �޸� ��뷮�� Ȯ���ϼ���.");
		break;
	case VERR_PARAMETER_IS_NOTALLOCATED:
		snprintf(pBuf, 1024, "�Ķ���Ϳ� ���� �޸� �Ҵ��� �̷������ ���� ���¿��� ��� ������ �Ұ����մϴ�.");
		break;
	case VERR_BAD_GROUP_IN_CONV2D_LAYER:
		snprintf(pBuf, 1024, "������� ���̾ �߸��� group ��(%s mod %s is not zero)�� �����Ǿ����ϴ�.", p1, p2);
		break;
	case VERR_BAD_HEAD_CNT_FOR_MH_ATTENTION:
		snprintf(pBuf, 1024, "��Ƽ��� ���ټ��� ���� ũ�⿡ ���յ��� �ʴ� �����Դϴ�.");
		break;
	case VERR_BAD_KQV_SHAPE_FOR_MH_ATTENTION:
		snprintf(pBuf, 1024, "��Ƽ��� ���ټ��� Ű, ����, ��� ������ ������ ��ġ���� �ʽ��ϴ�.");
		break;
	case VERR_PRUNING_WITHOUT_NAME:
		snprintf(pBuf, 1024, "�̸� ���� ���� pruning �бⰡ ���Ǿ����ϴ�. �ǵ����� ó����� drop ���� true�� �ּ���.");
		break;
	case VERR_GETNAME_NOT_FOUND:
		snprintf(pBuf, 1024, "%s ���̾�� get �Ӽ����� ������ %s ���� �ش��ϴ� �ټ��� ã�� �� �����ϴ�.", p1, p2);
		break;
	case VERR_LOSS_TERM_NOT_FOUND:
		snprintf(pBuf, 1024, "�ս� �Լ� ���ǿ� ������ %s �̸��� �ټ� ������ ã�� �� �����ϴ�.", p1);
		break;
	case VERR_BAD_SHAPE_FOR_IMAGE_LAYER:
		snprintf(pBuf, 1024, "�̹��� ó���� %s ������ ���յ��� �ʴ� ���� %s�� �־������ϴ�.", p1, p2);
		break;
	case VERR_RECURSIVE_MODULE_STRUCTURE:
		snprintf(pBuf, 1024, "��� %s�� ��� %s ���̿� ��ȯ ������ ����� �θ�-�ڽ� ���� ������ �䱸�Ǿ����ϴ�.", p1, p2);
		break;
	case VERR_UNMATCH_ON_TENSOR_DATATYPE:
		snprintf(pBuf, 1024, "%s Ÿ���� �ټ��� �ʿ��� ó���� %s Ÿ�� �ټ��� �߸� �����Ǿ����ϴ�.", p1, p2);
		break;
	case VERR_MODULE_EXPAND_FAILURE:
		snprintf(pBuf, 1024, "%s Ÿ���� ����� �����ϴ� �������� �߻��Ͽ����ϴ�.", p1);
		break;
	case VERR_UNKNWON_SHAPE_FOR_GET_FIELD:
		snprintf(pBuf, 1024, "get �ʵ�� ������ %s �Է� �ټ��� ������ �������� �ʾҽ��ϴ�.", p1);
		break;
	default:
		snprintf(pBuf, 1024, "�����޽����� �غ���� �ʾҽ��ϴ�.(code:%d,%s,%s)", nErrCode, p1, p2);
		break;
	}
}