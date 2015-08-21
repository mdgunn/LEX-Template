--[[
Purpose: A relay that fires random outputs when triggered
]]--

--KeyValues
Script.enabled=true--bool "Start On"
Script.MaxOut=9--int "Max Output"

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
		local chance = math.floor(Math:Random(1, self.MaxOut)) --Math:Random(1, 5)
		if chance == 1 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out1'.")
			self.component:CallOutputs("Out1")
		end
		if chance == 2 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out2'.")
			self.component:CallOutputs("Out2")
		end
		if chance == 3 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out3'.")
			self.component:CallOutputs("Out3")
		end
		if chance == 4 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out4'.")
			self.component:CallOutputs("Out4")
		end
		if chance == 5 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out5'.")
			self.component:CallOutputs("Out5")
		end
		if chance == 6 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out6'.")
			self.component:CallOutputs("Out6")
		end
		if chance == 7 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out7'.")
			self.component:CallOutputs("Out7")
		end
		if chance == 8 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out8'.")
			self.component:CallOutputs("Out8")
		end
		if chance == 9 then
			System:Print( "Entity: " ..self.entity:GetKeyValue("name") .." is firing output 'Out9'.")
			self.component:CallOutputs("Out9")
		end		
	end
end