--[[
Purpose: A simple relay to place in-between nodes of the flowgraph.
If you're coming from Source, you will know how to use them, and how 
useful they are!
	
For the rest of you, this will make it so a door by a trigger
will not open unless you press a switch or something. Think of it 
as a switch.
]]--

--KeyValues
Script.enabled=true--bool "Start Enabled"

function Script:Start()
	WidgetSprite:Create(self.entity)

	--To make making a Auto script, lets do this here.
	--On the map spawn, the relay will send an output.
	self.component:CallOutputs("OnSpawn")
end

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

function Script:Trigger()--in
	if self.enabled then
		self.component:CallOutputs("Trigger")
	end
end