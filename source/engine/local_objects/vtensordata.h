#pragma once

#include "../api/vcommon.h"
#include "../api_objects/vsession.h"

class VTensorDataCore;

class VTensorData {
public:
	VTensorData();
	VTensorData(VSession session, string sBuiltin, VDict kwArgs = {});
	VTensorData(const VTensorData& src);
	VTensorData(VTensorDataCore* core);
	virtual ~VTensorData();
	VTensorData& operator =(const VTensorData& src);
	VTensorDataCore* getClone();
	VTensorDataCore* getCore();
	void destroyCore();
	VSession session() const;
	bool isValid();
	int getRefCnt();
	int getNth();
protected:
	VTensorDataCore* m_core;

public:
	VTensorData(VSession session, int64 byteSize, int device);

	int64 byte_size();
	int device();

	void* void_ptr() const;
	int* int_ptr() const;
	int64* int64_ptr() const;
	float* float_ptr() const;
	unsigned char* uchar_ptr() const;

	// �Ʒ��� ��ɵ��� tracer ���뿡 ���ص��� �ʴ��� ����Ͽ� �˸°� ó���� ��
	void uploadData(void* pData, int64 nByteSize);
	void downloadData(void* pData, int64 nByteSize);

	//void copyFrom(VData src);

	void setZero();

	void memset(int value);
	void fill_float(float value);
	void init_random_normal(float mean, float init_arg, bool adaptive);
	void init_random_uniform(float mean, float init_arg);
	};
