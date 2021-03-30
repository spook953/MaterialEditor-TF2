#pragma once
#include "../AppSystem/AppSystem.h"

class IInputSystem : public IAppSystem
{
public:
	virtual void AttachToWindow(void *hWnd) = 0;
	virtual void DetachFromWindow() = 0;
	virtual void EnableInput(bool bEnable) = 0;
	virtual void EnableMessagePump(bool bEnable) = 0;
	virtual void PollInputState() = 0;
	virtual int GetPollTick() const = 0;
	virtual bool IsButtonDown(ButtonCode_t code) const = 0;
	virtual int GetButtonPressedTick(ButtonCode_t code) const = 0;
	virtual int GetButtonReleasedTick(ButtonCode_t code) const = 0;
	virtual int GetAnalogValue(AnalogCode_t code) const = 0;
	virtual int GetAnalogDelta(AnalogCode_t code) const = 0;
	virtual int GetEventCount() const = 0;
	virtual const InputEvent_t *GetEventData() const = 0;
	virtual void PostUserEvent(const InputEvent_t &event) = 0;
	virtual int GetJoystickCount() const = 0;
	virtual void EnableJoystickInput(int nJoystick, bool bEnable) = 0;
	virtual void EnableJoystickDiagonalPOV(int nJoystick, bool bEnable) = 0;
	virtual void SampleDevices(void) = 0;
	virtual void SetRumble(float fLeftMotor, float fRightMotor, int userId) = 0;
	virtual void StopRumble(void) = 0;
	virtual void ResetInputState() = 0;
};

inline IInputSystem *g_pInputSystem;