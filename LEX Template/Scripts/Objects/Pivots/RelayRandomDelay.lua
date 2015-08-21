--[[
Purpose: A random delay relay to place in-between nodes of the flowgraph.
Same as delay relay, but it fires an output after a random amount of time.
]]--

Script.enabled = true -- bool "Start On"
Script.FireTime = Vec2(0.1,1) --Vec2 "Delay Time"
Script.Timer = 0
Script.triggered = false

function Script:Start()
	WidgetSprite:Create(self.entity)
end

function Script:UpdateWorld()
	if self.enabled then
		if self.triggered then
			self.Timer = self.Timer + (Time:GetSpeed() /100)
			local chance = Math:Random(self.FireTime.x, self.FireTime.y)
			if self.Timer > chance then
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