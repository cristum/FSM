#include <iostream>
#include "FSM.h"
using namespace std;
// 간단 FSM 테스트 
class CTestFSM : public CFSM
{
public:
	// 이벤트 정의
	enum evtRunner 
	{
		evtCoinDrop = 0,
		evtSomeoneAskMe,
		evtRainDrop
	};

public:
	CTestFSM()
	{
		STATE(&CTestFSM::OnStand)//기본상태는 서있는상태로 시작.
	}

	// 상태핸들러  
	int OnStand(CFSM_EVT e);
	int OnRun(CFSM_EVT e);
	int OnSit(CFSM_EVT e);
	int OnStop(CFSM_EVT e);
};

// 서있는 상태...
int CTestFSM::OnStand(CFSM_EVT e)
{
	cout << "(서있음.)\r\n";

	BEGIN_EVT_MAP(e)

		ONEVENT(CTestFSM::evtCoinDrop) //서있는 상태로 해당 이벤트 발생시
		cout << "돈떨어졌다. 앉아야겠다.\r\n"; // 문장출력후
	PASS_EVT(&CTestFSM::OnSit) //행동 상태를 앉음으로 변경

		ONEVENT(CTestFSM::evtSomeoneAskMe) // 서있는 상태로 해당이벤트 발생시
		cout << "뭐 때문에 그러셔요..?\r\n"; //해당 문장 출력후
	END_EVT // 이벤트 종료

		ONEVENT(CTestFSM::evtRainDrop) //서있는 상태로 해당 이벤트 발생시
		cout << "비온다...!!\r\n"; // 해당 문장을 출력후
	PASS_EVT(&CTestFSM::OnRun) // 행동 상태를 달리는 상태로 변경

	END_EVT_MAP //

	return CFSM::COMPLETE; //처리 완료
}
// 뛰는 상태
int CTestFSM::OnRun(CFSM_EVT e)
{
	cout << "(뛰는중.)\r\n";

	BEGIN_EVT_MAP(e)

		ONEVENT(CTestFSM::evtCoinDrop)
		cout << "무슨소리지..?\r\n";
	PASS_EVT(&CTestFSM::OnStop)

		ONEVENT(CTestFSM::evtSomeoneAskMe)
		cout << "엇. 말시키네..?..?\r\n";
	PASS_EVT(&CTestFSM::OnStop)

		ONEVENT(CTestFSM::evtRainDrop)
		cout << "계속 뛴다.\r\n";
	END_EVT

	END_EVT_MAP

	return CFSM::COMPLETE;
}

// 앉아있는 상태
int CTestFSM::OnSit(CFSM_EVT e)
{
	cout << "(앉아있음.)\r\n";

	BEGIN_EVT_MAP(e)

		ONEVENT(CTestFSM::evtCoinDrop)
		cout << "돈줍고 일어서자.\r\n";
	STATE(&CTestFSM::OnStand)
		END_EVT

		ONEVENT(CTestFSM::evtSomeoneAskMe)
		cout << ">>일어난다.\r\n";
	PASS_EVT(&CTestFSM::OnStand)

		ONEVENT(CTestFSM::evtRainDrop)
		cout << ">>일어난다.";
	PASS_EVT(&CTestFSM::OnStand)

	END_EVT_MAP

	return CFSM::COMPLETE;
}

// 생각하는 상태
int CTestFSM::OnStop(CFSM_EVT e)
{
	cout << "(멈춘상태.)\r\n";

	BEGIN_EVT_MAP(e)

		ONEVENT(CTestFSM::evtCoinDrop)
		cout << ">>서서생각해보자 !!\r\n";
	PASS_EVT(&CTestFSM::OnStand)

		ONEVENT(CTestFSM::evtSomeoneAskMe)
		cout << ">>서서생각해보자 !!\r\n";
	PASS_EVT(&CTestFSM::OnStand)

	END_EVT_MAP

	return CFSM::COMPLETE;
}

int main(int argc, char** argv)
{
	CTestFSM f; //테스트FSM f
	CFSM_EVT e; //이벤트를 담는 e

	cout << ">>>>>>>동전떨어짐 \r\n";
	e.EVT = CTestFSM::evtCoinDrop;
	f.DoEvent(e);

	cout << ">>>>>>>누가물어봄 \r\n";
	e.EVT = CTestFSM::evtSomeoneAskMe;
	f.DoEvent(e);

	cout << ">>>>>>>비가떨어짐 \r\n";
	e.EVT = CTestFSM::evtRainDrop;
	f.DoEvent(e);

	cout << ">>>>>>>누가물어봄 \r\n";
	e.EVT = CTestFSM::evtSomeoneAskMe; //
	f.DoEvent(e);

	return 0;
}
