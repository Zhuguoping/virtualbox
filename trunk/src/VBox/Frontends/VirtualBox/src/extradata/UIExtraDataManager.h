/* $Id$ */
/** @file
 * VBox Qt GUI - UIExtraDataManager class declaration.
 */

/*
 * Copyright (C) 2010-2016 Oracle Corporation
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 */

#ifndef ___UIExtraDataManager_h___
#define ___UIExtraDataManager_h___

/* Qt includes: */
#include <QObject>
#include <QMap>
#ifdef VBOX_GUI_WITH_EXTRADATA_MANAGER_UI
# include <QPointer>
#endif /* VBOX_GUI_WITH_EXTRADATA_MANAGER_UI */
#include <QSize>

/* GUI includes: */
#include "UIExtraDataDefs.h"

/* Forward declarations: */
class UIExtraDataEventHandler;
#ifdef VBOX_GUI_WITH_EXTRADATA_MANAGER_UI
class UIExtraDataManagerWindow;
#endif /* VBOX_GUI_WITH_EXTRADATA_MANAGER_UI */

/** Defines the map of extra data values. The index is an extra-data key. */
typedef QMap<QString, QString> ExtraDataMap;
/** Defines the map of extra data maps. The index is a UUID string. */
typedef QMap<QString, ExtraDataMap> MapOfExtraDataMaps;

/** Singleton QObject extension
  * providing GUI with corresponding extra-data values,
  * and notifying it whenever any of those values changed. */
class UIExtraDataManager : public QObject
{
    Q_OBJECT;

    /** Extra-data Manager constructor. */
    UIExtraDataManager();
    /** Extra-data Manager destructor. */
    ~UIExtraDataManager();

signals:

    /** Notifies about extra-data map acknowledging. */
    void sigExtraDataMapAcknowledging(QString strID);

    /** Notifies about extra-data change. */
    void sigExtraDataChange(QString strID, QString strKey, QString strValue);

    /** Notifies about GUI language change. */
    void sigLanguageChange(QString strLanguage);

    /** Notifies about Selector UI keyboard shortcut change. */
    void sigSelectorUIShortcutChange();
    /** Notifies about Runtime UI keyboard shortcut change. */
    void sigRuntimeUIShortcutChange();
    /** Notifies about Runtime UI host-key combination change. */
    void sigRuntimeUIHostKeyCombinationChange();

    /** Notifies about menu-bar configuration change. */
    void sigMenuBarConfigurationChange(const QString &strMachineID);
    /** Notifies about status-bar configuration change. */
    void sigStatusBarConfigurationChange(const QString &strMachineID);

    /** Notifies about HID LEDs synchronization state change. */
    void sigHidLedsSyncStateChange(bool fEnabled);

    /** Notifies about the scale-factor change. */
    void sigScaleFactorChange(const QString &strMachineID);

    /** Notifies about the scaling optimization type change. */
    void sigScalingOptimizationTypeChange(const QString &strMachineID);

    /** Notifies about the HiDPI optimization type change. */
    void sigHiDPIOptimizationTypeChange(const QString &strMachineID);

    /** Notifies about unscaled HiDPI output mode change. */
    void sigUnscaledHiDPIOutputModeChange(const QString &strMachineID);

#ifdef RT_OS_DARWIN
    /** Mac OS X: Notifies about 'dock icon' appearance change. */
    void sigDockIconAppearanceChange(bool fEnabled);
    /** Mac OS X: Notifies about 'dock icon overlay' appearance change. */
    void sigDockIconOverlayAppearanceChange(bool fEnabled);
#endif /* RT_OS_DARWIN */

public:

    /** Global extra-data ID. */
    static const QString GlobalID;

    /** Static Extra-data Manager instance/constructor. */
    static UIExtraDataManager* instance();
    /** Static Extra-data Manager destructor. */
    static void destroy();

#ifdef VBOX_GUI_WITH_EXTRADATA_MANAGER_UI
    /** Static show and raise API. */
    static void openWindow(QWidget *pCenterWidget);
#endif /* VBOX_GUI_WITH_EXTRADATA_MANAGER_UI */

    /** @name Base
      * @{ */
        /** Returns whether Extra-data Manager cached the map with passed @a strID. */
        bool contains(const QString &strID) const { return m_data.contains(strID); }
        /** Returns read-only extra-data map for passed @a strID. */
        const ExtraDataMap map(const QString &strID) const { return m_data.value(strID); }

        /** Hot-load machine extra-data map. */
        void hotloadMachineExtraDataMap(const QString &strID);

        /** Returns extra-data value corresponding to passed @a strKey as QString.
          * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
        QString extraDataString(const QString &strKey, const QString &strID = GlobalID);
        /** Defines extra-data value corresponding to passed @a strKey as strValue.
          * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
        void setExtraDataString(const QString &strKey, const QString &strValue, const QString &strID = GlobalID);

        /** Returns extra-data value corresponding to passed @a strKey as QStringList.
          * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
        QStringList extraDataStringList(const QString &strKey, const QString &strID = GlobalID);
        /** Defines extra-data value corresponding to passed @a strKey as value.
          * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
        void setExtraDataStringList(const QString &strKey, const QStringList &value, const QString &strID = GlobalID);
    /** @} */

    /** @name General
      * @{ */
        /** Returns event handling type. */
        EventHandlingType eventHandlingType();
    /** @} */

    /** @name Messaging
      * @{ */
        /** Returns the list of supressed messages for the Message/Popup center frameworks. */
        QStringList suppressedMessages(const QString &strID = GlobalID);
        /** Defines the @a list of supressed messages for the Message/Popup center frameworks. */
        void setSuppressedMessages(const QStringList &list);

        /** Returns the list of messages for the Message/Popup center frameworks with inverted check-box state. */
        QStringList messagesWithInvertedOption();

#if !defined(VBOX_BLEEDING_EDGE) && !defined(DEBUG)
        /** Returns version for which user wants to prevent BETA build warning. */
        QString preventBetaBuildWarningForVersion();
#endif /* !defined(VBOX_BLEEDING_EDGE) && !defined(DEBUG) */
    /** @} */

#ifdef VBOX_GUI_WITH_NETWORK_MANAGER
    /** @name Application Update
      * @{ */
        /** Returns whether Application Update functionality enabled. */
        bool applicationUpdateEnabled();

        /** Returns Application Update data. */
        QString applicationUpdateData();
        /** Defines Application Update data as @a strValue. */
        void setApplicationUpdateData(const QString &strValue);

        /** Returns Application Update check counter. */
        qulonglong applicationUpdateCheckCounter();
        /** Increments Application Update check counter. */
        void incrementApplicationUpdateCheckCounter();
    /** @} */
#endif /* VBOX_GUI_WITH_NETWORK_MANAGER */

    /** @name Settings
      * @{ */
        /** Returns whether GUI @a enmFeature is enabled. */
        bool guiFeatureEnabled(GUIFeatureType enmFeature);

        /** Returns restricted global settings pages. */
        QList<GlobalSettingsPageType> restrictedGlobalSettingsPages();
        /** Returns restricted machine settings pages. */
        QList<MachineSettingsPageType> restrictedMachineSettingsPages(const QString &strID);
    /** @} */

    /** @name Settings: General
      * @{ */
        /** Returns whether the host screen-saver should be disabled. */
        bool hostScreenSaverDisabled();
        /** Defines whether the host screen-saver should be @a fDisabled. */
        void setHostScreenSaverDisabled(bool fDisabled);
    /** @} */

    /** @name Settings: Language
      * @{ */
        /** Returns the GUI language ID. */
        QString languageId();
        /** Defines the GUI @a strLanguageId. */
        void setLanguageId(const QString &strLanguageId);
    /** @} */

    /** @name Settings: Display
      * @{ */
        /** Returns maximum guest-screen resolution policy. */
        MaxGuestResolutionPolicy maxGuestResolutionPolicy();
        /** Defines maximum guest-screen resolution @a enmPolicy or @a resolution itself for Fixed policy. */
        void setMaxGuestScreenResolution(MaxGuestResolutionPolicy enmPolicy, const QSize resolution = QSize());
        /** Returns maximum guest-screen resolution for fixed policy. */
        QSize maxGuestResolutionForPolicyFixed();
        /** Defines maximum guest-screen @a resolution for fixed policy. */
        void setMaxGuestResolutionForPolicyFixed(const QSize &resolution);

        /** Returns whether hovered machine-window should be activated. */
        bool activateHoveredMachineWindow();
        /** Defines whether hovered machine-window should be @a fActivated. */
        void setActivateHoveredMachineWindow(bool fActivate);
    /** @} */

    /** @name Settings: Keyboard
      * @{ */
        /** Returns the Runtime UI host-key combination. */
        QString hostKeyCombination();
        /** Defines the Runtime UI host-key combination. */
        void setHostKeyCombination(const QString &strHostCombo);

        /** Returns shortcut overrides for shortcut-pool with @a strPoolExtraDataID. */
        QStringList shortcutOverrides(const QString &strPoolExtraDataID);

        /** Returns whether the Runtime UI auto-capture is enabled. */
        bool autoCaptureEnabled();
        /** Defines whether the Runtime UI auto-capture is @a fEnabled. */
        void setAutoCaptureEnabled(bool fEnabled);

        /** Returns the Runtime UI remapped scan codes. */
        QString remappedScanCodes();
    /** @} */

    /** @name Settings: Proxy
      * @{ */
        /** Returns VBox proxy settings. */
        QString proxySettings();
        /** Defines VBox proxy @a strSettings. */
        void setProxySettings(const QString &strSettings);
    /** @} */

    /** @name Settings: Storage
      * @{ */
        /** Returns recent folder for hard-drives. */
        QString recentFolderForHardDrives();
        /** Returns recent folder for optical-disks. */
        QString recentFolderForOpticalDisks();
        /** Returns recent folder for floppy-disks. */
        QString recentFolderForFloppyDisks();
        /** Defines recent folder for hard-drives as @a strValue. */
        void setRecentFolderForHardDrives(const QString &strValue);
        /** Defines recent folder for optical-disk as @a strValue. */
        void setRecentFolderForOpticalDisks(const QString &strValue);
        /** Defines recent folder for floppy-disk as @a strValue. */
        void setRecentFolderForFloppyDisks(const QString &strValue);

        /** Returns the list of recently used hard-drives. */
        QStringList recentListOfHardDrives();
        /** Returns the list of recently used optical-disk. */
        QStringList recentListOfOpticalDisks();
        /** Returns the list of recently used floppy-disk. */
        QStringList recentListOfFloppyDisks();
        /** Defines the list of recently used hard-drives as @a value. */
        void setRecentListOfHardDrives(const QStringList &value);
        /** Defines the list of recently used optical-disks as @a value. */
        void setRecentListOfOpticalDisks(const QStringList &value);
        /** Defines the list of recently used floppy-disks as @a value. */
        void setRecentListOfFloppyDisks(const QStringList &value);
    /** @} */

    /** @name VirtualBox Manager
      * @{ */
        /** Returns selector-window geometry using @a pWidget as the hint. */
        QRect selectorWindowGeometry(QWidget *pWidget);
        /** Returns whether selector-window should be maximized. */
        bool selectorWindowShouldBeMaximized();
        /** Defines selector-window @a geometry and @a fMaximized state. */
        void setSelectorWindowGeometry(const QRect &geometry, bool fMaximized);

        /** Returns selector-window splitter hints. */
        QList<int> selectorWindowSplitterHints();
        /** Defines selector-window splitter @a hints. */
        void setSelectorWindowSplitterHints(const QList<int> &hints);

        /** Returns whether selector-window tool-bar visible. */
        bool selectorWindowToolBarVisible();
        /** Defines whether selector-window tool-bar @a fVisible. */
        void setSelectorWindowToolBarVisible(bool fVisible);

        /** Returns whether selector-window status-bar visible. */
        bool selectorWindowStatusBarVisible();
        /** Defines whether selector-window status-bar @a fVisible. */
        void setSelectorWindowStatusBarVisible(bool fVisible);

        /** Clears all the existing selector-window chooser-pane' group definitions. */
        void clearSelectorWindowGroupsDefinitions();
        /** Returns selector-window chooser-pane' groups definitions for passed @a strGroupID. */
        QStringList selectorWindowGroupsDefinitions(const QString &strGroupID);
        /** Defines selector-window chooser-pane' groups @a definitions for passed @a strGroupID. */
        void setSelectorWindowGroupsDefinitions(const QString &strGroupID, const QStringList &definitions);

        /** Returns last-item ID of the item chosen in selector-window chooser-pane. */
        QString selectorWindowLastItemChosen();
        /** Defines @a lastItemID of the item chosen in selector-window chooser-pane. */
        void setSelectorWindowLastItemChosen(const QString &strItemID);

        /** Returns selector-window details-pane' elements. */
        QMap<DetailsElementType, bool> selectorWindowDetailsElements();
        /** Defines selector-window details-pane' @a elements. */
        void setSelectorWindowDetailsElements(const QMap<DetailsElementType, bool> &elements);

        /** Returns selector-window details-pane' preview update interval. */
        PreviewUpdateIntervalType selectorWindowPreviewUpdateInterval();
        /** Defines selector-window details-pane' preview update @a interval. */
        void setSelectorWindowPreviewUpdateInterval(PreviewUpdateIntervalType interval);
    /** @} */

    /** @name Wizards
      * @{ */
        /** Returns mode for wizard of passed @a type. */
        WizardMode modeForWizardType(WizardType type);
        /** Defines @a mode for wizard of passed @a type. */
        void setModeForWizardType(WizardType type, WizardMode mode);
    /** @} */

    /** @name Virtual Machine
      * @{ */
        /** Returns whether machine should be shown in selector-window chooser-pane. */
        bool showMachineInSelectorChooser(const QString &strID);
        /** Returns whether machine should be shown in selector-window details-pane. */
        bool showMachineInSelectorDetails(const QString &strID);

        /** Returns whether machine reconfiguration enabled. */
        bool machineReconfigurationEnabled(const QString &strID);
        /** Returns whether machine snapshot operations enabled. */
        bool machineSnapshotOperationsEnabled(const QString &strID);

        /** Returns whether this machine is first time started. */
        bool machineFirstTimeStarted(const QString &strID);
        /** Returns whether this machine is fFirstTimeStarted. */
        void setMachineFirstTimeStarted(bool fFirstTimeStarted, const QString &strID);

        /** Except Mac OS X: Returns redefined machine-window icon names. */
        QStringList machineWindowIconNames(const QString &strID);
#ifndef VBOX_WS_MAC
        /** Except Mac OS X: Returns redefined machine-window name postfix. */
        QString machineWindowNamePostfix(const QString &strID);
#endif /* !VBOX_WS_MAC */

        /** Returns geometry for machine-window with @a uScreenIndex in @a visualStateType. */
        QRect machineWindowGeometry(UIVisualStateType visualStateType, ulong uScreenIndex, const QString &strID);
        /** Returns whether machine-window with @a uScreenIndex in @a visualStateType should be maximized. */
        bool machineWindowShouldBeMaximized(UIVisualStateType visualStateType, ulong uScreenIndex, const QString &strID);
        /** Defines @a geometry and @a fMaximized state for machine-window with @a uScreenIndex in @a visualStateType. */
        void setMachineWindowGeometry(UIVisualStateType visualStateType, ulong uScreenIndex, const QRect &geometry, bool fMaximized, const QString &strID);

#ifndef VBOX_WS_MAC
        /** Returns whether Runtime UI menu-bar is enabled. */
        bool menuBarEnabled(const QString &strID);
        /** Defines whether Runtime UI menu-bar is @a fEnabled. */
        void setMenuBarEnabled(bool fEnabled, const QString &strID);
#endif /* !VBOX_WS_MAC */

        /** Returns whether Runtime UI menu-bar context-menu is enabled. */
        bool menuBarContextMenuEnabled(const QString &strID);
        /** Defines whether Runtime UI menu-bar context-menu is @a fEnabled. */
        void setMenuBarContextMenuEnabled(bool fEnabled, const QString &strID);

        /** Returns restricted Runtime UI menu types. */
        UIExtraDataMetaDefs::MenuType restrictedRuntimeMenuTypes(const QString &strID);
        /** Defines restricted Runtime UI menu types. */
        void setRestrictedRuntimeMenuTypes(UIExtraDataMetaDefs::MenuType types, const QString &strID);

        /** Returns restricted Runtime UI action types for Application menu. */
        UIExtraDataMetaDefs::MenuApplicationActionType restrictedRuntimeMenuApplicationActionTypes(const QString &strID);
        /** Defines restricted Runtime UI action types for Application menu. */
        void setRestrictedRuntimeMenuApplicationActionTypes(UIExtraDataMetaDefs::MenuApplicationActionType types, const QString &strID);

        /** Returns restricted Runtime UI action types for Machine menu. */
        UIExtraDataMetaDefs::RuntimeMenuMachineActionType restrictedRuntimeMenuMachineActionTypes(const QString &strID);
        /** Defines restricted Runtime UI action types for Machine menu. */
        void setRestrictedRuntimeMenuMachineActionTypes(UIExtraDataMetaDefs::RuntimeMenuMachineActionType types, const QString &strID);

        /** Returns restricted Runtime UI action types for View menu. */
        UIExtraDataMetaDefs::RuntimeMenuViewActionType restrictedRuntimeMenuViewActionTypes(const QString &strID);
        /** Defines restricted Runtime UI action types for View menu. */
        void setRestrictedRuntimeMenuViewActionTypes(UIExtraDataMetaDefs::RuntimeMenuViewActionType types, const QString &strID);

        /** Returns restricted Runtime UI action types for Input menu. */
        UIExtraDataMetaDefs::RuntimeMenuInputActionType restrictedRuntimeMenuInputActionTypes(const QString &strID);
        /** Defines restricted Runtime UI action types for Input menu. */
        void setRestrictedRuntimeMenuInputActionTypes(UIExtraDataMetaDefs::RuntimeMenuInputActionType types, const QString &strID);

        /** Returns restricted Runtime UI action types for Devices menu. */
        UIExtraDataMetaDefs::RuntimeMenuDevicesActionType restrictedRuntimeMenuDevicesActionTypes(const QString &strID);
        /** Defines restricted Runtime UI action types for Devices menu. */
        void setRestrictedRuntimeMenuDevicesActionTypes(UIExtraDataMetaDefs::RuntimeMenuDevicesActionType types, const QString &strID);

#ifdef VBOX_WITH_DEBUGGER_GUI
        /** Returns restricted Runtime UI action types for Debugger menu. */
        UIExtraDataMetaDefs::RuntimeMenuDebuggerActionType restrictedRuntimeMenuDebuggerActionTypes(const QString &strID);
        /** Defines restricted Runtime UI action types for Debugger menu. */
        void setRestrictedRuntimeMenuDebuggerActionTypes(UIExtraDataMetaDefs::RuntimeMenuDebuggerActionType types, const QString &strID);
#endif /* VBOX_WITH_DEBUGGER_GUI */

#ifdef VBOX_WS_MAC
        /** Mac OS X: Returns restricted Runtime UI action types for Window menu. */
        UIExtraDataMetaDefs::MenuWindowActionType restrictedRuntimeMenuWindowActionTypes(const QString &strID);
        /** Mac OS X: Defines restricted Runtime UI action types for Window menu. */
        void setRestrictedRuntimeMenuWindowActionTypes(UIExtraDataMetaDefs::MenuWindowActionType types, const QString &strID);
#endif /* VBOX_WS_MAC */

        /** Returns restricted Runtime UI action types for Help menu. */
        UIExtraDataMetaDefs::MenuHelpActionType restrictedRuntimeMenuHelpActionTypes(const QString &strID);
        /** Defines restricted Runtime UI action types for Help menu. */
        void setRestrictedRuntimeMenuHelpActionTypes(UIExtraDataMetaDefs::MenuHelpActionType types, const QString &strID);

        /** Returns restricted Runtime UI visual-states. */
        UIVisualStateType restrictedVisualStates(const QString &strID);

        /** Returns requested Runtime UI visual-state. */
        UIVisualStateType requestedVisualState(const QString &strID);
        /** Defines requested Runtime UI visual-state as @a visualState. */
        void setRequestedVisualState(UIVisualStateType visualState, const QString &strID);

#ifdef VBOX_WS_X11
        /** Returns whether legacy full-screen mode is requested. */
        bool legacyFullscreenModeRequested();
#endif /* VBOX_WS_X11 */

        /** Returns whether guest-screen auto-resize according machine-window size is enabled. */
        bool guestScreenAutoResizeEnabled(const QString &strID);
        /** Defines whether guest-screen auto-resize according machine-window size is @a fEnabled. */
        void setGuestScreenAutoResizeEnabled(bool fEnabled, const QString &strID);

        /** Returns last guest-screen visibility status for screen with @a uScreenIndex. */
        bool lastGuestScreenVisibilityStatus(ulong uScreenIndex, const QString &strID);
        /** Defines whether last guest-screen visibility status was @a fEnabled for screen with @a uScreenIndex. */
        void setLastGuestScreenVisibilityStatus(ulong uScreenIndex, bool fEnabled, const QString &strID);

        /** Returns last guest-screen size-hint for screen with @a uScreenIndex. */
        QSize lastGuestScreenSizeHint(ulong uScreenIndex, const QString &strID);
        /** Defines last guest-screen @a sizeHint for screen with @a uScreenIndex. */
        void setLastGuestScreenSizeHint(ulong uScreenIndex, const QSize &sizeHint, const QString &strID);

        /** Returns host-screen index corresponding to passed guest-screen @a iGuestScreenIndex. */
        int hostScreenForPassedGuestScreen(int iGuestScreenIndex, const QString &strID);
        /** Defines @a iHostScreenIndex corresponding to passed guest-screen @a iGuestScreenIndex. */
        void setHostScreenForPassedGuestScreen(int iGuestScreenIndex, int iHostScreenIndex, const QString &strID);

        /** Returns whether automatic mounting/unmounting of guest-screens enabled. */
        bool autoMountGuestScreensEnabled(const QString &strID);

#ifdef VBOX_WITH_VIDEOHWACCEL
        /** Returns whether 2D acceleration should use linear sretch. */
        bool useLinearStretch(const QString &strID);
        /** Returns whether 2D acceleration should use YV12 pixel format. */
        bool usePixelFormatYV12(const QString &strID);
        /** Returns whether 2D acceleration should use UYVY pixel format. */
        bool usePixelFormatUYVY(const QString &strID);
        /** Returns whether 2D acceleration should use YUY2 pixel format. */
        bool usePixelFormatYUY2(const QString &strID);
        /** Returns whether 2D acceleration should use AYUV pixel format. */
        bool usePixelFormatAYUV(const QString &strID);
#endif /* VBOX_WITH_VIDEOHWACCEL */

        /** Returns whether Runtime UI should use unscaled HiDPI output. */
        bool useUnscaledHiDPIOutput(const QString &strID);
        /** Defines whether Runtime UI should @a fUseUnscaledHiDPIOutput. */
        void setUseUnscaledHiDPIOutput(bool fUseUnscaledHiDPIOutput, const QString &strID);

        /** Returns Runtime UI HiDPI optimization type. */
        HiDPIOptimizationType hiDPIOptimizationType(const QString &strID);

#ifndef VBOX_WS_MAC
        /** Returns whether mini-toolbar is enabled for full and seamless screens. */
        bool miniToolbarEnabled(const QString &strID);
        /** Defines whether mini-toolbar is @a fEnabled for full and seamless screens. */
        void setMiniToolbarEnabled(bool fEnabled, const QString &strID);

        /** Returns whether mini-toolbar should auto-hide itself. */
        bool autoHideMiniToolbar(const QString &strID);
        /** Defines whether mini-toolbar should @a fAutoHide itself. */
        void setAutoHideMiniToolbar(bool fAutoHide, const QString &strID);

        /** Returns mini-toolbar alignment. */
        Qt::AlignmentFlag miniToolbarAlignment(const QString &strID);
        /** Returns mini-toolbar @a alignment. */
        void setMiniToolbarAlignment(Qt::AlignmentFlag alignment, const QString &strID);
#endif /* VBOX_WS_MAC */

        /** Returns whether Runtime UI status-bar is enabled. */
        bool statusBarEnabled(const QString &strID);
        /** Defines whether Runtime UI status-bar is @a fEnabled. */
        void setStatusBarEnabled(bool fEnabled, const QString &strID);

        /** Returns whether Runtime UI status-bar context-menu is enabled. */
        bool statusBarContextMenuEnabled(const QString &strID);
        /** Defines whether Runtime UI status-bar context-menu is @a fEnabled. */
        void setStatusBarContextMenuEnabled(bool fEnabled, const QString &strID);

        /** Returns restricted Runtime UI status-bar indicator list. */
        QList<IndicatorType> restrictedStatusBarIndicators(const QString &strID);
        /** Defines restricted Runtime UI status-bar indicator @a list. */
        void setRestrictedStatusBarIndicators(const QList<IndicatorType> &list, const QString &strID);

        /** Returns Runtime UI status-bar indicator order list. */
        QList<IndicatorType> statusBarIndicatorOrder(const QString &strID);
        /** Defines Runtime UI status-bar indicator order @a list. */
        void setStatusBarIndicatorOrder(const QList<IndicatorType> &list, const QString &strID);

#ifdef VBOX_WS_MAC
        /** Mac OS X: Returns whether Dock icon should be updated at runtime. */
        bool realtimeDockIconUpdateEnabled(const QString &strID);
        /** Mac OS X: Defines whether Dock icon update should be fEnabled at runtime. */
        void setRealtimeDockIconUpdateEnabled(bool fEnabled, const QString &strID);

        /** Mac OS X: Returns guest-screen which Dock icon should reflect at runtime. */
        int realtimeDockIconUpdateMonitor(const QString &strID);
        /** Mac OS X: Defines guest-screen @a iIndex which Dock icon should reflect at runtime. */
        void setRealtimeDockIconUpdateMonitor(int iIndex, const QString &strID);

        /** Mac OS X: Returns whether Dock icon overlay is disabled. */
        bool dockIconDisableOverlay(const QString &strID);
        /** Mac OS X: Defines whether Dock icon overlay is @a fDisabled. */
        void setDockIconDisableOverlay(bool fDisabled, const QString &strID);
#endif /* VBOX_WS_MAC */

        /** Returns whether machine should pass CAD to guest. */
        bool passCADtoGuest(const QString &strID);

        /** Returns the mouse-capture policy. */
        MouseCapturePolicy mouseCapturePolicy(const QString &strID);

        /** Returns redefined guru-meditation handler type. */
        GuruMeditationHandlerType guruMeditationHandlerType(const QString &strID);

        /** Returns whether machine should perform HID LEDs synchronization. */
        bool hidLedsSyncState(const QString &strID);

        /** Returns the scale-factor. */
        double scaleFactor(const QString &strID);
        /** Defines the @a dScaleFactor. */
        void setScaleFactor(double dScaleFactor, const QString &strID);

        /** Returns the scaling optimization type. */
        ScalingOptimizationType scalingOptimizationType(const QString &strID);
    /** @} */

    /** @name Virtual Machine: Information dialog
      * @{ */
        /** Returns information-window geometry using @a pWidget and @a pParentWidget as hints. */
        QRect informationWindowGeometry(QWidget *pWidget, QWidget *pParentWidget, const QString &strID);
        /** Returns whether information-window should be maximized or not. */
        bool informationWindowShouldBeMaximized(const QString &strID);
        /** Defines information-window @a geometry and @a fMaximized state. */
        void setInformationWindowGeometry(const QRect &geometry, bool fMaximized, const QString &strID);

        /** Returns information-window elements. */
        QMap<InformationElementType, bool> informationWindowElements();
        /** Defines information-window @a elements. */
        void setInformationWindowElements(const QMap<InformationElementType, bool> &elements);
    /** @} */

    /** @name Virtual Machine: Close dialog
      * @{ */
        /** Returns default machine close action. */
        MachineCloseAction defaultMachineCloseAction(const QString &strID);
        /** Returns restricted machine close actions. */
        MachineCloseAction restrictedMachineCloseActions(const QString &strID);

        /** Returns last machine close action. */
        MachineCloseAction lastMachineCloseAction(const QString &strID);
        /** Defines last @a machineCloseAction. */
        void setLastMachineCloseAction(MachineCloseAction machineCloseAction, const QString &strID);

        /** Returns machine close hook script name as simple string. */
        QString machineCloseHookScript(const QString &strID);
    /** @} */

#ifdef VBOX_WITH_DEBUGGER_GUI
    /** @name Virtual Machine: Debug UI
      * @{ */
        /** Returns debug flag value for passed @a strDebugFlagKey. */
        QString debugFlagValue(const QString &strDebugFlagKey);
    /** @} */
#endif /* VBOX_WITH_DEBUGGER_GUI */

#ifdef VBOX_GUI_WITH_EXTRADATA_MANAGER_UI
    /** @name VirtualBox: Extra-data Manager window
      * @{ */
        /** Returns Extra-data Manager geometry using @a pWidget as hint. */
        QRect extraDataManagerGeometry(QWidget *pWidget);
        /** Returns whether Extra-data Manager should be maximized or not. */
        bool extraDataManagerShouldBeMaximized();
        /** Defines Extra-data Manager @a geometry and @a fMaximized state. */
        void setExtraDataManagerGeometry(const QRect &geometry, bool fMaximized);

        /** Returns Extra-data Manager splitter hints using @a pWidget as hint. */
        QList<int> extraDataManagerSplitterHints(QWidget *pWidget);
        /** Defines Extra-data Manager splitter @a hints. */
        void setExtraDataManagerSplitterHints(const QList<int> &hints);
    /** @} */
#endif /* VBOX_GUI_WITH_EXTRADATA_MANAGER_UI */

    /** @name Virtual Machine: Log dialog
      * @{ */
        /** Returns log-window geometry using @a pWidget and @a defaultGeometry as hints. */
        QRect logWindowGeometry(QWidget *pWidget, const QRect &defaultGeometry);
        /** Returns whether log-window should be maximized or not. */
        bool logWindowShouldBeMaximized();
        /** Defines log-window @a geometry and @a fMaximized state. */
        void setLogWindowGeometry(const QRect &geometry, bool fMaximized);
    /** @} */

private slots:

    /** Handles 'extra-data change' event: */
    void sltExtraDataChange(QString strMachineID, QString strKey, QString strValue);

private:

    /** Prepare Extra-data Manager. */
    void prepare();
    /** Prepare global extra-data map. */
    void prepareGlobalExtraDataMap();
    /** Prepare extra-data event-handler. */
    void prepareExtraDataEventHandler();
#ifdef VBOX_GUI_WITH_EXTRADATA_MANAGER_UI
    // /** Prepare window. */
    // void prepareWindow();

    /** Cleanup window. */
    void cleanupWindow();
#endif /* VBOX_GUI_WITH_EXTRADATA_MANAGER_UI */
    /** Cleanup extra-data event-handler. */
    void cleanupExtraDataEventHandler();
    // /** Cleanup extra-data map. */
    // void cleanupExtraDataMap();
    /** Cleanup Extra-data Manager. */
    void cleanup();

#ifdef VBOX_GUI_WITH_EXTRADATA_MANAGER_UI
    /** Open window. */
    void open(QWidget *pCenterWidget);
#endif /* VBOX_GUI_WITH_EXTRADATA_MANAGER_UI */

    /** Retrieves an extra-data key from both machine and global sources.
      *
      * If @a strID isn't #GlobalID, this will first check the extra-data associated
      * with the machine given by @a strID then fallback on the global extra-data.
      *
      * @returns String value if found, null string if not.
      * @param   strKey      The extra-data key to get.
      * @param   strID       Machine UUID or #GlobalID.
      * @param   strValue    Where to return the value when found. */
    QString extraDataStringUnion(const QString &strKey, const QString &strID);
    /** Determines whether feature corresponding to passed @a strKey is allowed.
      * If valid @a strID is set => applies to machine and global extra-data,
      * otherwise => only to global one. */
    bool isFeatureAllowed(const QString &strKey, const QString &strID = GlobalID);
    /** Determines whether feature corresponding to passed @a strKey is restricted.
      * If valid @a strID is set => applies to machine and global extra-data,
      * otherwise => only to global one. */
    bool isFeatureRestricted(const QString &strKey, const QString &strID = GlobalID);

    /** Translates bool flag into QString value. */
    QString toFeatureState(bool fState);
    /** Translates bool flag into 'allowed' value. */
    QString toFeatureAllowed(bool fAllowed);
    /** Translates bool flag into 'restricted' value. */
    QString toFeatureRestricted(bool fRestricted);

    /** Returns string consisting of @a strBase appended with @a uScreenIndex for the *non-primary* screen-index.
      * If @a fSameRuleForPrimary is 'true' same rule will be used for *primary* screen-index. Used for storing per-screen extra-data. */
    static QString extraDataKeyPerScreen(const QString &strBase, ulong uScreenIndex, bool fSameRuleForPrimary = false);

    /** Singleton Extra-data Manager instance. */
    static UIExtraDataManager *m_spInstance;

    /** Holds extra-data event-handler instance. */
    UIExtraDataEventHandler *m_pHandler;

    /** Holds extra-data map instance. */
    MapOfExtraDataMaps m_data;

#ifdef VBOX_GUI_WITH_EXTRADATA_MANAGER_UI
    /** Holds Extra-data Manager window instance. */
    QPointer<UIExtraDataManagerWindow> m_pWindow;
#endif /* VBOX_GUI_WITH_EXTRADATA_MANAGER_UI */
};

/** Singleton Extra-data Manager 'official' name. */
#define gEDataManager UIExtraDataManager::instance()

#endif /* !___UIExtraDataManager_h___ */

