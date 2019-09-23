#pragma once
#include "sdk_util.h"
#include "custom_ui_base.h"

class CCustomizeUIVideoFlow
{
public:
	CCustomizeUIVideoFlow();
	~CCustomizeUIVideoFlow();
	void SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent* pEvent);
	void Show();
	void SetVideoContainer(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* pContainer);
	void Reset();
		
	bool DestroryVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement);
	bool CreateVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement** pVideoElement,ZOOM_SDK_NAMESPACE::VideoRenderElementType type);

	bool ShowPreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement, RECT rc);
	bool HidePreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement);

	bool ShowActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement, RECT rc);
	bool HideActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement);

	bool ShowGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, RECT rc);
	bool HideGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement);
	bool SubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID);
	bool UnSubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID);
	
	bool SetVideoElementPos(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement, RECT rc);

	void HandleSizeChanged(RECT newRC);
private:
	ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* m_pVideoContainer;
};
