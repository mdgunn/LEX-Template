--[[ 
Purpose: Fires an output after a certain amount of time. It will keep looping 
until it's disabled. If you want a delayed event, RelayDelay.lua is what you're looking for.
]]--

Script.enabled = true -- bool "Start Enabled"
Script.FireTime = 1.0 -- float "Respawn time"
Script.Timer = 0

function Script:Start()
	WidgetSprite:Create(self.entity)
end

function Script:UpdateWorld()
	if self.enabled then
		self.Timer = self.Timer + (Time:GetSpeed() /100)
		if self.Timer > self.FireTime then
			self.component:CallOutputs("OnTimer")
			self.Timer = 0 
		end
	end
end

--[[
function Script:EditMaxTime(MaxTime)--in
	self.Timer = 0
	self.FireTime = MaxTime
end
]]--

function Script:Enable()--in
	if self.enabled==false then
		self.enabled=true
		self.component:CallOutputs("Enable")
	end
end

function Script:Disable()--in
	if self.enabled then
		self.enabled=false
		self.component:CallOutputs("Disable")
	end
end
