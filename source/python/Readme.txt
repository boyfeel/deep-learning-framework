################################################################################

[ README ]

kai -> kai_torchtest -> src -> api_python -> sample
  convert_sample
    unit test file
  reference
    tut_ver01 : konanai_cpp.exe�� ��� �� ����
    tut_ver02 : konanai_cpp.exe�� ��� �� �Ұ���
  ������ ����
    model sample : konanai_cpp.exe�� ��� �� ����

kai -> work -> cache -> tconn_python
  �ش� ������ �ݵ�� �����ؾ� �� : work ���� ���� ������ ���鵵�� ���� �ʿ��غ���

################################################################################

[ �۾� ���ǻ��� ]

KONANAI_PATH ȯ�溯�� �ʿ�
  - C:\ ����� ���� ��� \kai2021\

Visual Studio 2019
  - CUDA
    CUDA 11.3�� Visual Studio 2022 �����Ϸ� ���� ����
  
  - x64-Release Mode ���
    x64-Debug Mode�� ���� �� Python ��Ű�� �� ����� ��� ���� ���ϴ� ��� ���� ����

  - CMake ����
    Tools -> Options -> CMake -> General -> When cache is out of date
    Never run configure step automatically �� ����

  - ��, �鿩���� ������
    ���� -> �ɼ� -> �ؽ�Ʈ ������ -> C/C++ -> ��
    �� ũ�� : 4
    �鿩���� ũ�� : 4

Python 3.9
  - KONANAI_PYTHON_PATH ȯ�溯�� �ʿ�
    ������ ���
      C:\Users\����� �̸�\AppData\Local\Programs\Python\Python39
    ���� ȯ���� ���
      ����ȯ���� Python PATH
  - ����� ���̺귯�� ���
    ������ -> �� �� ��� -> Python -> ���� -> Modify -> Optional Feature -> Next -> Advanced Options
    Download debugging symbols
    Download debug binaries (requires VS 2017 or later)

  - Python Package Install
    kai -> konanai -> src
    setup.py
    requirements.txt
    �ַܼ� �̵� ( cmd, git bash, etc ... )
    conda ����ڴ� ����ȯ�� Ȱ��ȭ �� ����
    - ���ļ�ġ (���� ����) : 'pip install .'
    - �����ڸ�� ��ġ (���� ��ũ ����) : 'pip install -e .'

RESTfulAPI
  - cpp SDK ��ġ �ʿ�
    [ Installation : Environment ]
    vcpkg  : https://github.com/Microsoft/vcpkg
    https://github.com/microsoft/vcpkg/blob/master/README_ko_KR.md
    git bash
    cd c: && git clone https://github.com/microsoft/vcpkg
    ./vcpkg/bootstrap-vcpkg.bat
    [ Installation : cpprsetsdk ****2.10.18**** ]
    https://github.com/microsoft/cpprestsdk/blob/master/README.md
    API Document : https://microsoft.github.io/cpprestsdk/namespaces.html
    Sample Code : https://github.com/Microsoft/cpprestsdk/wiki/Samples
    cd c: && cd vcpkg
    ./vcpkg install cpprestsdk cpprestsdk:x64-windows
    ./vcpkg integrate install
  - sample code
    [ example ]
      kai -> konanai -> src -> api_python -> sample -> restful
      restful_server_sample.py ���� : (�系 ��Ʈ��ũ�� ����ũ�� 1 ���� ���� -> ����ũ�� 1�� Addr �Է�)
      restful_client_sample.py ���� : (�系 ��Ʈ��ũ�� ����ũ�� 2 ���� ���� -> ����ũ�� 1�� Addr �Է�)
    [ server sample code ]
      RESTfulAPI* TestServer;
      TestServer = new RESTfulAPI("http://xxx.xxx.xxx.xxx:xxxx", true, false);
      delete TestServer;
    [ client sample code ]
      RESTfulAPI* TestClient;
      TestClient = new RESTfulAPI("http://xxx.xxx.xxx.xxx:xxxx", false, true);
      TestClient->Sample_ClientAsyncRequestGET();
      TestClient->Sample_ClientAsyncRequestPUT();
      delete TestClient;

vcpkg
  - ��ɾ� ����
    x32 ��Ű�� ��ġ : ./vcpkg install [package name]
    x64 ��Ű�� ��ġ : ./vcpkg install [package name]:x64-windows
    Example : x32 x64 ��Ű�� ���� ��ġ : ./vcpkg install [package name] [package name]:x64-windows

kai2021-> kai-> CMakeLists.txt
  - ����ȯ�� ������� �ʴ� ��� �Ʒ� ���� �ּ�ó��
    file(COPY "C:/ProgramData/Miniconda3/envs/AI-DF/python39.dll"
    DESTINATION  ${CMAKE_BINARY_DIR}/..)
    file(COPY "C:/ProgramData/Miniconda3/envs/AI-DF/python39_d.dll"
    DESTINATION  ${CMAKE_BINARY_DIR}/..)

################################################################################

Python sample file Ȱ���� ���� �ʿ��� packages
  1. struct (as st)
  2. numpy (as np)
  3. os, sys
  4. time
  5. math
  6. pathlib�� Path

Ȱ�� �� �ʿ��� �κ�
  - Tonumpy_Mnist_train( ), Tonumpy_Mnist_test( ) �Լ����� ���� image, label�� array�� �޾ƿ��� ���ؼ�
    �ֻ�ܿ��� data_types��, Tonumpy_Mnist_train( ) �Լ� ������ nDim, dataType, dataFormat, dataSize�� global�� ���� �ʿ�
  - path ���� Ȱ���� ���� �Ʒ� �ڵ� �ۼ� (���� ������ �ڵ忡���� ������� �ʾ����� ���� cache ���� �� ��� ����)
	curdir = os.path.dirname(__file__)
	pardir = Path(curdir).parent.parent
	abspardir = os.path.abspath(pardir)
	sys.path.append(abspardir)

################################################################################