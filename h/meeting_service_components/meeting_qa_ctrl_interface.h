/*!
* \file meeting_qa_ctrl_interface.h
* \brief Meeting Service qa Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_QA_CTRL_INTERFACE_H_
#define _MEETING_QA_CTRL_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum QAConnectStatus
    \brief Information category for Q&A connecting.
    Here are more detailed structural descriptions.
*/
enum QAConnectStatus
{
	QA_STATUS_CONNECTING = 0,
	QA_STATUS_CONNECTED,
	QA_STATUS_DISCONNECTED,
	QA_STATUS_DISCONNECT_CONFLICT,
};

/// \brief answer item interface class
class IAnswerItem
{
public:
	virtual ~IAnswerItem(){}

	virtual time_t  GetTimeStamp() = 0;
	virtual const wchar_t* GetText() = 0;
	virtual const wchar_t* GetSenderName() = 0;
	virtual const wchar_t* GetQuestionID() = 0;
	virtual const wchar_t* GetAnswerID() = 0;

	virtual bool IsPrivate() = 0;
	virtual bool IsLiveAnswer() = 0;
	virtual bool IsSenderMyself() = 0;
};

/// \brief question item interface class
class IQAItemInfo
{
public:
	virtual ~IQAItemInfo() {}

	virtual time_t GetTimeStamp() = 0;
	virtual unsigned int GetUpvoteNum() = 0;
	virtual const wchar_t* GetText() = 0;
	virtual const wchar_t* GetSenderName() = 0;
	virtual const wchar_t* GetQuestionID() = 0;

	virtual bool IsAnonymous() = 0;
	virtual bool IsMarkedAsAnswered() = 0;
	virtual bool IsMarkedAsDismissed() = 0;
	virtual bool IsSenderMyself() = 0;
	virtual bool IsMySelfUpvoted() = 0;

	virtual bool HasLiveAnswers() = 0;
	virtual bool HasTextAnswers() = 0;
	virtual bool AmILiveAnswering() = 0;
	virtual const wchar_t* GetLiveAnswerName() = 0;
	virtual bool IsLiveAnswering() = 0;
	
	//answer list!
	virtual IList<IAnswerItem*>* GetAnswerList() = 0;
};

/// \brief Meeting q&a callback event.
///
class IMeetingQAControllerEvent
{
public:
	/// \brief Callback event of Q&A connecting status. 
	/// \param connectStatus: The value of Q&A connecting status. For more details, see \link QAConnectStatus \endlink enum.
	virtual void OnQAConnectStatus(QAConnectStatus connectStatus) = 0;

	virtual void OnAddQuestion(const wchar_t* questionID, bool bSuccess) = 0;

	virtual void OnAddAnswer(const wchar_t* answerID, bool bSuccess) = 0;

	virtual void OnQuestionMarkedAsDismissed(const wchar_t* question_id) = 0;

	virtual void OnReopenQuestion(const wchar_t* question_id) = 0;

	virtual void OnReceiveQuestion(const wchar_t* questionID) = 0;

	virtual void OnReceiveAnswer(const wchar_t* answerID) = 0;

	virtual void OnUserLivingReply(const wchar_t* questionID) = 0;

	virtual void OnUserEndLiving(const wchar_t* questionID) = 0;

	virtual void OnUpvoteQuestion(const wchar_t* question_id, bool order_changed) = 0;

	virtual void OnRevokeUpvoteQuestion(const wchar_t* question_id, bool order_changed) = 0;

	virtual void OnAllowAskQuestionAnonymousStatus(bool bEnabled) = 0;

	virtual void OnAllowAttendeeViewAllQuestionStatus(bool bEnabled) = 0;

	virtual void OnAllowAttendeeVoteupQuestionStatus(bool bEnabled) = 0;

	virtual void OnAllowAttendeeCommentQuestionStatus(bool bEnabled) = 0;

	virtual void OnRefreshQAData() = 0;
};

class IMeetingQAController
{
public:
	virtual SDKError SetEvent(IMeetingQAControllerEvent* pEvent) = 0;

	//attendee
	virtual SDKError AddQuestion(const wchar_t* questionContent, bool bAskAnonymous) = 0;
	virtual int GetMyQuestionCount() = 0;
	virtual IList<IQAItemInfo *>* GetMyQuestionList() = 0;
	virtual SDKError CommentQuestion(const wchar_t* questionID, const wchar_t* commentContent) = 0;

	//host
	virtual SDKError AnswerQuestionPrivate(const wchar_t* questionID, const wchar_t* answerContent) = 0;
	virtual SDKError AnswerQuestionPublic(const wchar_t* questionID, const wchar_t* answerContent) = 0;
	virtual SDKError DismissQuestion(const wchar_t* questionID) = 0;
	virtual SDKError ReopenQuestion(const wchar_t* questionID) = 0;
	virtual SDKError StartLiving(const wchar_t* questionID) = 0;
	virtual SDKError EndLiving(const wchar_t* questionID) = 0;

	virtual int GetOpenQuestionCount() = 0;
	virtual int GetDismissedQuestionCount() = 0;
	virtual int GetAnsweredQuestionCount() = 0;
	virtual IList<IQAItemInfo *>* GetOpenQuestionList() = 0;
	virtual IList<IQAItemInfo *>* GetDismissedQuestionList() = 0;
	virtual IList<IQAItemInfo *>* GetAnsweredQuestionList() = 0;

	virtual SDKError EnableAnonnymousQuestion(bool bEnable) = 0;
	virtual SDKError EnableAttendeeViewAllQuestion(bool bEnable) = 0;
	virtual SDKError EnableQAComment(bool bEnable) = 0;
	virtual SDKError EnableQAVoteup(bool bEnable) = 0;

	//attendee & host
	virtual bool IsQAEnabled() = 0;
	virtual bool IsQACommentEnabled() = 0; 
	virtual bool IsQAVoteupEnabled() = 0;
	virtual bool IsAskQuestionAnonymouslyEnabled() = 0;
	virtual bool IsAttendeeCanViewAllQuestions()=0;
	virtual IList<IQAItemInfo *>* GetAllQuestionList() = 0;
	virtual IQAItemInfo* GetQuestion(const wchar_t* questionID) = 0;
	virtual IAnswerItem* GetAnswer(const wchar_t* answerID) = 0;
	virtual SDKError VoteupQuestion(const wchar_t* questionID, bool bVokeup) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif