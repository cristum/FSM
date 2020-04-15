#pragma once
#ifndef __PSW_SNAKE_CFSM_BASE__
#define __PSW_SNAKE_CFSM_BASE__

// 매크로 정의부
#define STATE( a ) SetAction( static_cast<CFSM::Action>( a )  );
#define BEGIN_EVT_MAP( e ) switch(e.EVT){ 
#define END_EVT_MAP }

#define CNT_EVT return CFSM::CONTINUE;
#define END_EVT break;

#define ONEVENT( a ) case a:
#define PASS_EVT( a )  STATE( a ) CNT_EVT;

// 이벤트와 매개변수
// 처리 클래스 
class CFSM_EVT
{
public:
	unsigned EVT;
	long     pParam;
};

// 한정상태기계(Finate State Machine)
// BASE 클래스 
class CFSM
{
public:
	typedef int (CFSM::*Action)(CFSM_EVT);
	CFSM() { StateHandler = &CFSM::doNothing; } // 상태핸들러엔 기본적으로 아무것도안하는 함수가 들어간다.

	enum state {
		COMPLETE = 0,  // 메시지 처리 완료
		CONTINUE       // 상태변화 메시지, 처리 진행 한번더..
	};

	// >>외부 이벤트 처리 
	// 설정된 이벤트와 상태값을 X,Y로
	// 핸들러테이블의 함수를 호출한다.
	void DoEvent(CFSM_EVT evt)
	{
		int nRst = 1;
		while (nRst)
		{
			nRst = (this->*StateHandler)(evt);
		}
	}

	// 아무것도 안하는 함수는 어디서나 필요하다.
	int doNothing(CFSM_EVT e) { return COMPLETE; }

protected:
	// 입력받은 상태를 상태핸들러에 전이한다.
	inline void SetAction(Action a)
	{
		StateHandler = a;
	}

private:
	Action   StateHandler;
};
#endif

