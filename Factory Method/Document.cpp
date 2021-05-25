// 출처 - https://cinrueom.tistory.com/34

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

//문서클래스의 최상위 클래스.
class Document
{
public:
	virtual bool Open(const char* pFileName) = 0;
};

//한글문서 클래스
class HwpDocument : public Document
{
public:
	bool Open(const char* pFileName)
	{
		ifstream ifs(pFileName);
		if (!ifs)
			return false;
		// -- HWP 고유 프로세싱
		return true;
	}
};

//워드문서 클래스
class MsWordDocument : public Document
{
public:
	bool Open(const char* pFileName)
	{
		ifstream ifs(pFileName);
		if (!ifs)
			return false;
		// -- MS-Word 고유 프로세싱
		return true;
	}
};

//응용프로그램 최상위 클래스.
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

//한글응용프로그램 클래스.
class HwpApplication : public Application
{
public:
	Document * CreateDocument()
	{
		return new HwpDocument;
	}
};

//워드응용프로그램 클래스.
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
	HwpApplication hwp;           //한글응용프로그램 객체 생성.
	hwp.NewDocument("input.hwp"); //한글문서 객체 생성.

	return 0;
}


