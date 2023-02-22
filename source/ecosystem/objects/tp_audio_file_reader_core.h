#pragma once

#include "../utils/tp_common.h"
#include "../objects/tp_nn.h"

class EAudioFileReaderCore : public VObjCore {
protected:
    friend class EAudioFileReader;
protected:
    EAudioFileReaderCore(ENN nn);
    ~EAudioFileReaderCore();
    EAudioFileReaderCore* clone() { return (EAudioFileReaderCore*)clone_core(); }

protected:
    void m_setup();
    void m_setup(VDict args);
    void m_delete();

    bool m_addFile(string filePath);
    
    ETensor m_get_fft_spectrums(bool ment);

protected:
    ENN m_nn;

    bool m_bBadFile;

    int64 m_freq_in_spectrum;  // �ϳ��� ���ļ� ����Ʈ���� ���� ���ļ� ����
    int64 m_fft_width;         // �� ���ļ� ����Ʈ�� �м��� �̿�� ����� ������ ��, 2�� �ŵ�����
    int64 m_spec_interval;     // ���ļ� ����Ʈ���� ���� ���ݿ� �ش��ϴ� ���� ��
    int64 m_spec_count;        // ����� Ư������ �߾� �������� ������ ����Ʈ�� ����
    int64 m_need_samples;      // ������ ����Ʈ�� ������ ����Ʈ�� ���� ����, ����Ʈ�� ���� ���̸� ����� ���� �ʿ� ���ü�

    vector<string> m_filePaths;
    vector<int64> m_offsets;

    int m_nTooShort;
    int m_nBadFormat;

protected:
    //void m_setup(string sName, string sBuiltin, VDict kwArgs);

protected:
    //string m_sBuiltin;
    //string m_sName;
};
