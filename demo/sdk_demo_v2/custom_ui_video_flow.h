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
		
	ZOOM_SDK_NAMESPACE::SDKError DestroryVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement);
	ZOOM_SDK_NAMESPACE::SDKError CreateVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement** pVideoElement,ZOOM_SDK_NAMESPACE::VideoRenderElementType type);

	ZOOM_SDK_NAMESPACE::SDKError ShowPreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement, RECT rc);
	ZOOM_SDK_NAMESPACE::SDKError HidePreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement);

	ZOOM_SDK_NAMESPACE::SDKError ShowActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement, RECT rc);
	ZOOM_SDK_NAMESPACE::SDKError HideActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement);

	ZOOM_SDK_NAMESPACE::SDKError ShowGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, RECT rc);
	ZOOM_SDK_NAMESPACE::SDKError HideGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement);
	ZOOM_SDK_NAMESPACE::SDKError SubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID);
	ZOOM_SDK_NAMESPACE::SDKError UnSubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID);
	
	ZOOM_SDK_NAMESPACE::SDKError SetVideoElementPos(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement, RECT rc);

	ZOOM_SDK_NAMESPACE::SDKError HandleSizeChanged(RECT newRC);
private:
	ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* m_pVideoContainer;
};
