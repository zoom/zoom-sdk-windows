#pragma once
#include "sdk_util.h"
#include "custom_ui_mgr.h"
#include <string>
#include <map>
#include "resource.h"
#include "custom_ui_base.h"
#include "custom_ui_video_flow.h"
#include "sdk_demo_app_common.h"

#define GalleryView_Need_Init -1
#define Custom_MeetingUI_Height  740
#define	Custom_MeetingUI_Width	 1660

#define VideoElement_Active_height 720
#define VideoElement_Active_width 1280

#define VideoElement_Normal_height 180
#define VideoElement_Normal_width 320

#define	Normal_SharingUI_Height	 810
#define Normal_SharingUI_Width	1600

#define Normal_PageButton_Height 40
#define Normal_Toolbar_Width 60

#define NormalVideo_Elem_MaxCount 6 

class CCustomizeInMeetingUIMgr;

class CCustomizeUIVideoMgr
{
public:
	CCustomizeUIVideoMgr(CCustomizeInMeetingUIMgr* pMainUI);
	void CreateCustomVideoContainer(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* pUIMgr, HWND hParent, RECT rc);
	void init();
	void uninit();
	void SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent* pEvent);
	void Show();
	void SetGalleryViewStatus(bool bIn);
	void CalulateViewRect();
	RECT GetCurrentAcviteViewRect();
	RECT GetCurrentGalleryViewRect();

	void HandleSizeChanged(RECT newRC);
	void HandleUserChanged();
	void HandleSwitchGalleryPage(ArrowButtonType btnType);
	void HandleVideoRenderElementDestroyed(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement);
	void HandleVideoContainerDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* pContainer);

	int getVideoGalleryPage();
	int getVideoGalleryCurrPage();

	void ShowPreviewVideo(RECT rc);
	void HidePreviewVideo();
	void DestroyPreviewVideo();

	void ShowActiveViewVideo();
	void HideActiveViewVideo();
	void DestroyActiveViewVideo();

	void CreateGalleryViewVideo();
	void ShowGalleryViewVideo(GalleryViewSubscribeType nType = GalleryView_Subscribe_CurrentPage);
	void HideGalleryViewVideo();
	void DestroyGalleryViewVideo();
	
private:
	void CalculateCountInOnePages();
	void CalculateTotalPages();
	void ReSubscribeNormalUser(GalleryViewSubscribeType nType);
	void DestroyCustomVideoContainer();
	void SetParentHWND(HWND parentHwnd) {m_hParentWnd = parentHwnd;};
	void CalculateCurrentActiveViewRect();
	void CalculateCurrentGalleryViewRect();
private:
	CCustomizeInMeetingUIMgr* m_pMainUI;
	ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* m_pCustomizedContainer;
	ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* m_pActiveElem;
	ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* m_pPreviewElem;
	ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* m_pNormalElemGallery[NormalVideo_Elem_MaxCount];
	HWND m_hParentWnd;
	RECT m_rcActiveView;
	RECT m_rcGalleryView;
	bool m_bIsGalleryViewShown;
	bool m_bNeedInitGalleryView;
	int m_iGalleryTotalPage;
	int m_iGalleryCurrentPage;
	int m_iVideoCountInOnePage;
	CCustomizeUIVideoFlow m_customUIVideoFlow;
};

