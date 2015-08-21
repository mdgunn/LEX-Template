--[[
Purpose: A delay relay to place in-between nodes of the flowgraph.
Same as the Relay, but it fires an output after X amount of time.
]]--

Script.enabled = true -- bool "Start On"
Script.FireTime = 1.0 -- float "Delay Time"
Script.Timer = 0
Script.triggered = false

function Script:Start()
	WidgetSprite:Create(self.entity)
	--To make making a Auto script, lets do this here.
	--On the map spawn, the relay will send an output.
	self.component:CallOutputs("OnSpawn")
end

function Script:UpdateWorld()
	if self.enabled then
		if self.triggered then
			self.Timer = self.Timer + (Time:GetSpeed() /100)
			if self.Timer > self.FireTime then
				self.component:CallOutputs("Trigger")
				self.Timer = 0 
				self.triggered = false
			end
		end
	end
end

function Script:Trigger()--in
	if self.enabled then
		self.triggered = true
	end
end

function Script:Enable()--in
	if self.enabled==false then
		self.enabled=true
		--self.component:CallOutputs("Enable")
	end
end

function Script:Disable()--in
	if self.enabled then
		self.enabled=false
		--self.component:CallOutputs("Disable")
	end
end