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
	QA_STATUS_CONNECTING = 0,///<Connecting.
	QA_STATUS_CONNECTED,///<Connected.
	QA_STATUS_DISCONNECTED,///<Disconnected.
	QA_STATUS_DISCONNECT_CONFLICT,///<Disconnected because of conflict.
};

/// \brief Answer item interface class
class IAnswerItem
{
public:
	virtual ~IAnswerItem(){}
	
	/// \brief Get the timestamp of the answer.
	/// \return The timestamp of the answer.
	virtual time_t  GetTimeStamp() = 0;
	
	/// \brief Get the text of the answer.
	/// \return The text of the answer.
	virtual const wchar_t* GetText() = 0;
	
	/// \brief Get the sender's name of the answer.
	/// \return The sender's name of the answer.
	virtual const wchar_t* GetSenderName() = 0;
	
	/// \brief Get the related question's id of the answer.
	/// \return The related question's id of the answer.
	virtual const wchar_t* GetQuestionID() = 0;
	
	/// \brief Get the answer id.
	/// \return The answer id.
	virtual const wchar_t* GetAnswerID() = 0;
	
	/// \brief Determine if the answer is private or not.
	/// \return TRUE indicates to the answer is private.
	virtual bool IsPrivate() = 0;
	
	/// \brief Determine if the answer is live or not.
	/// \return TRUE indicates to the answer is live.
	virtual bool IsLiveAnswer() = 0;
	
	/// \brief Determine whether the answer's sender is the user himself or not.
	/// \return TRUE indicates that the answer's sender is the user himself.
	virtual bool IsSenderMyself() = 0;
};

/// \brief Question item interface class
class IQAItemInfo
{
public:
	virtual ~IQAItemInfo() {}

	/// \brief Get the timestamp of the question.
	/// \return The timestamp of the question.
	virtual time_t GetTimeStamp() = 0;
	
	/// \brief Get the number of the up_voters of the question.
	/// \return The number of the up_voters of the question.
	virtual unsigned int GetUpvoteNum() = 0;
	
	/// \brief Get the text of the question.
	/// \return The text of the question.
	virtual const wchar_t* GetText() = 0;
	
	/// \brief Get the sender's name of the question.
	/// \return The sender's name of the question.
	virtual const wchar_t* GetSenderName() = 0;
	
	/// \brief Get the question id.
	/// \return The question id.
	virtual const wchar_t* GetQuestionID() = 0;

	/// \brief Determine if the question is anonymous.
	/// \return TRUE indicates the question is anonymous. 
	virtual bool IsAnonymous() = 0;
	
	/// \brief Determine if the question is marked as answered.
	/// \return TURE indicates the question is marked as answered.
	virtual bool IsMarkedAsAnswered() = 0;
	
	/// \brief Determine if the question is marked as dismissed.
	/// \return TRUE indicates the question is marked as dismissed.
	virtual bool IsMarkedAsDismissed() = 0;
	
	/// \brief Determine if the question's sender is the user himself or not.
	/// \return TRUE indicates that the question's sender is the user himself.
	virtual bool IsSenderMyself() = 0;
	
	/// \brief Determine if the user himself is an up_voter of the question or not.
	/// \return TRUE indicates the user himself is an up_voter of the question.
	virtual bool IsMySelfUpvoted() = 0;

	/// \brief Determine if the question has live answers or not.
	/// \return TRUE indicates the question has live answers.
	virtual bool HasLiveAnswers() = 0;
	
	/// \brief Determine if the question has text answers or not.
	/// \return TRUE indicates the question has text answers.
	virtual bool HasTextAnswers() = 0;
	
	/// \brief Determine if the user himself is answering the question live or not.
	/// \return TRUE indicates the user himself is answering the question live.
	virtual bool AmILiveAnswering() = 0;
	
	/// \brief Get all the users' names who answers the question live.
	/// \return All the users' names who answers the question live. Separated by commas.
	virtual const wchar_t* GetLiveAnswerName() = 0;
	
	/// \brief Determine if the question is being answered live or not.
	/// \return TRUE indicates the question is being answered live.
	virtual bool IsLiveAnswering() = 0;
	
	/// \brief Get the list of all the answers to the question.
	/// \return The list of all the answers to the question. For more details, see \link IAnswerItem \endlink.
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
	
	/// \brief Callback event of adding question.
	/// \param questionID The question id.
	/// \param bSuccess Add question successfully or not.
	virtual void OnAddQuestion(const wchar_t* questionID, bool bSuccess) = 0;

	/// \brief Callback event of adding answer.
	/// \param answerID The answer id.
	/// \param bSuccess Add answer successfully or not.
	virtual void OnAddAnswer(const wchar_t* answerID, bool bSuccess) = 0;

	/// \brief Callback event of marking question as dismissed.
	/// \param question_id The question id.
	virtual void OnQuestionMarkedAsDismissed(const wchar_t* question_id) = 0;

	/// \brief Callback event of reopening question.
	/// \param question_id The question id.
	virtual void OnReopenQuestion(const wchar_t* question_id) = 0;

	/// \brief Callback event of receiving question.
	/// \param questionID The question id.
	virtual void OnReceiveQuestion(const wchar_t* questionID) = 0;

	/// \brief Callback event of receiving answer.
	/// \param answerID The answer id.
	virtual void OnReceiveAnswer(const wchar_t* answerID) = 0;

	/// \brief Callback event of user answering live.
	/// \param questionID The question id.
	virtual void OnUserLivingReply(const wchar_t* questionID) = 0;
	
	/// \brief Callback event of end of user answering live. 
	/// \param questionID The question id.
	virtual void OnUserEndLiving(const wchar_t* questionID) = 0;

	/// \brief Callback event of voting up question.
	/// \param question_id The question id.
	/// \param order_changed The order of the question in question list is changed or not.
	virtual void OnUpvoteQuestion(const wchar_t* question_id, bool order_changed) = 0;
	
	/// \brief Callback event of revoking voting up question.
	/// \param question_id The question id.
	/// \param order_changed The order of the question in question list is changed or not.
	virtual void OnRevokeUpvoteQuestion(const wchar_t* question_id, bool order_changed) = 0;

	/// \brief Callback event of deleting question(s).
	/// \param lstQuestionID The list of question ids.
	virtual void OnDeleteQuestion(IList<const wchar_t*>* lstQuestionID) = 0;

	/// \brief Callback event of  deleting answer(s).
	/// \param lstAnswerID The list of answer ids.
	virtual void OnDeleteAnswer(IList<const wchar_t*>* lstAnswerID) = 0;

	/// \brief Callback event of enabling to ask question anonymously.
	/// \param bEnabled Enbabled or not.
	virtual void OnAllowAskQuestionAnonymousStatus(bool bEnabled) = 0;
	
	/// \brief Callback event of enabling attendee to view all questions.
	/// \param bEnabled Enbabled or not.
	virtual void OnAllowAttendeeViewAllQuestionStatus(bool bEnabled) = 0;

	/// \brief Callback event of enabling attendee to vote up questions.
	/// \param bEnabled Enbabled or not.
	virtual void OnAllowAttendeeVoteupQuestionStatus(bool bEnabled) = 0;

	/// \brief Callback event of enabling attendee to comment questions.
	/// \param bEnabled Enbabled or not.
	virtual void OnAllowAttendeeCommentQuestionStatus(bool bEnabled) = 0;

	/// \brief Callback event of refreshing q&a data.
	virtual void OnRefreshQAData() = 0;
};

/// \brief Meeting q&a controller interface class.
///
class IMeetingQAController
{
public:
	/// \brief Set the meeting q&a controller callback event handler.
	/// \param pEvent A pointer to the IMeetingQAControllerEvent that receives the meeting q&a event. For more details, see \link IMeetingQAControllerEvent \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingQAControllerEvent* pEvent) = 0;

	//attendee
	
	/// \brief The attendee adds a question.
	/// \param questionContent Specifies the content of the question.
	/// \param bAskAnonymous Specifies whether the question is asked anonymously.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AddQuestion(const wchar_t* questionContent, bool bAskAnonymous) = 0;
	
	/// \brief Get the question count of the attendee himself.
	/// \return The question count of the attendee himself.
	virtual int GetMyQuestionCount() = 0;
	
	/// \brief Get the list of all the questions that the attendee himself added.
	/// \return The list of all the questions that the attendee himself added. For more details, see \link IQAItemInfo \endlink.
	virtual IList<IQAItemInfo *>* GetMyQuestionList() = 0;
	
	/// \brief The attendee comments a question.
	/// \param questionID Specifies the question id.
	/// \param commentContent Specifies the content of the comment.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The comment will be cut off if it is over long.
	virtual SDKError CommentQuestion(const wchar_t* questionID, const wchar_t* commentContent) = 0;

	//host
	
	/// \brief The host answers the question to the question sender privately.
	/// \param questionID Specifies the question id.
	/// \param answerContent Specifies the content of the answer.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The answer will be cut off if it is over long.
	virtual SDKError AnswerQuestionPrivate(const wchar_t* questionID, const wchar_t* answerContent) = 0;
	
	/// \brief The host answers the question publicly.
	/// \param questionID Specifies the question id.
	/// \param answerContent Specifies the content of the answer.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The answer will be cut off if it is over long.
	virtual SDKError AnswerQuestionPublic(const wchar_t* questionID, const wchar_t* answerContent) = 0;
	
	/// \brief The host dismisses the question.
	/// \param questionID Specifies the question id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DismissQuestion(const wchar_t* questionID) = 0;

	/// \brief The host deletes the question.
	/// \param questionID Specifies the question id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DeleteQuestion(const wchar_t* questionID) = 0;

	/// \brief The host deletes the answerID.
	/// \param answerID Specifies the answer id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DeleteAnswer(const wchar_t* answerID) = 0;

	/// \brief The host reopens the question.
	/// \param questionID Specifies the question id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ReopenQuestion(const wchar_t* questionID) = 0;
	
	/// \brief Set the question can be answered live.
	/// \param questionID Specifies the question id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartLiving(const wchar_t* questionID) = 0;
	
	/// \brief Set the question can not be answered live.
	/// \param questionID Specifies the question id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EndLiving(const wchar_t* questionID) = 0;

	/// \brief Get the count of the opened questions.
	/// \return The count of the opened questions.
	virtual int GetOpenQuestionCount() = 0;
	
	/// \brief Get the count of the dismissed questions.
	/// \return The count of the dismissed questions.
	virtual int GetDismissedQuestionCount() = 0;
	
	/// \brief Get the count of the answered questions.
	/// \return The count of the answered questions.
	virtual int GetAnsweredQuestionCount() = 0;
	
	/// \brief Get the list of the opened questions.
	/// \return The list of the opened questions. For more details, see \link IQAItemInfo \endlink.
	virtual IList<IQAItemInfo *>* GetOpenQuestionList() = 0;
	
	/// \brief Get the list of the dismissed questions.
	/// \return The list of the dismissed questions. For more details, see \link IQAItemInfo \endlink.
	virtual IList<IQAItemInfo *>* GetDismissedQuestionList() = 0;
	
	/// \brief Get the list of the answered questions.
	/// \return The list of the answered questions. For more details, see \link IQAItemInfo \endlink.
	virtual IList<IQAItemInfo *>* GetAnsweredQuestionList() = 0;
	
	/// \brief Enable or disable to ask question anonymously.
	/// \param bEnable TRUE indicates to enable to ask question anonymously.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAnonnymousQuestion(bool bEnable) = 0;
	
	/// \brief Enable or disable the attendees to view all the questions.
	/// \param bEnable TRUE indicates to enable the attendees to view all the questions.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAttendeeViewAllQuestion(bool bEnable) = 0;
	
	/// \brief Enable or disable to comment question.
	/// \param bEnable TRUE indicates to enable to comment question.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableQAComment(bool bEnable) = 0;
	
	/// \brief Enable or disable to vote up question.
	/// \param bEnable TRUE indicates to enable to vote up question.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableQAVoteup(bool bEnable) = 0;

	//attendee & host
	
	/// \brief Determine if the meeting q&a service is enabled.
	/// \return TRUE indicates the meeting q&a service is enabled.
	virtual bool IsQAEnabled() = 0;
	
	/// \brief Determine if enabled to comment question.
	/// \return TRUE indicates enabled.
	virtual bool IsQACommentEnabled() = 0; 
	
	/// \brief Determine if enabled to vote up question.
	/// \return TRUE indicates enabled.
	virtual bool IsQAVoteupEnabled() = 0;
	
	/// \brief Determine if enabled to ask question anonymously.
	/// \return TRUE indicates enabled.
	virtual bool IsAskQuestionAnonymouslyEnabled() = 0;
	
	/// \brief Determine if the attendee can view all the questions.
	/// \return TRUE indicates the attendee can view all the questions.
	virtual bool IsAttendeeCanViewAllQuestions()=0;
	
	/// \brief Get the list of all the questions.
	/// \return The list of all the questions. For more details, see \link IQAItemInfo \endlink.
	virtual IList<IQAItemInfo *>* GetAllQuestionList() = 0;
	
	/// \brief Get a certain question.
	/// \param questionID Specifies the question id.
	/// \return A pointer to IQAItemInfo. For more details, see \link IQAItemInfo \endlink.
	virtual IQAItemInfo* GetQuestion(const wchar_t* questionID) = 0;
	
	/// \brief Get a certain answer.
	/// \param answerID Specifies the answer id.
	/// \return A pointer to IAnswerItem. For more details, see \link IAnswerItem \endlink.
	virtual IAnswerItem* GetAnswer(const wchar_t* answerID) = 0;
	
	/// \brief Vote up or revoke voting up the question.
	/// \param questionID Specifies the question id.
	/// \param bVokeup TRUE indicates to vote up, FALSE indicates to revoke voting up.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError VoteupQuestion(const wchar_t* questionID, bool bVokeup) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif