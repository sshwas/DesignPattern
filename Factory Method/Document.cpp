// ��ó - https://cinrueom.tistory.com/34

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

//����Ŭ������ �ֻ��� Ŭ����.
class Document
{
public:
	virtual bool Open(const char* pFileName) = 0;
};

//�ѱ۹��� Ŭ����
class HwpDocument : public Document
{
public:
	bool Open(const char* pFileName)
	{
		ifstream ifs(pFileName);
		if (!ifs)
			return false;
		// -- HWP ���� ���μ���
		return true;
	}
};

//���幮�� Ŭ����
class MsWordDocument : public Document
{
public:
	bool Open(const char* pFileName)
	{
		ifstream ifs(pFileName);
		if (!ifs)
			return false;
		// -- MS-Word ���� ���μ���
		return true;
	}
};

//�������α׷� �ֻ��� Ŭ����.
class Application
{
private:
	map<STRING, *Document> docs_;

public:
	void NewDocument(const char* pFileName)
	{
		Document *pDoc = CreateDocument();
		docs_[pFileName] = pDoc;
		pDoc->Open(pFileName);
	}

	virtual Document* CreateDocument() = 0;
};

//�ѱ��������α׷� Ŭ����.
class HwpApplication : public Application
{
public:
	Document * CreateDocument()
	{
		return new HwpDocument;
	}
};

//�����������α׷� Ŭ����.
class MsWordApplication : public Application
{
public:
	Document * CreateDocument()
	{
		return new MsWordDocument;
	}
};


int main()
{
	HwpApplication hwp;           //�ѱ��������α׷� ��ü ����.
	hwp.NewDocument("input.hwp"); //�ѱ۹��� ��ü ����.

	return 0;
}


