--[[
Purpose:  This script will make any entity act as a collision trigger.  It works best when you set the
entity's collision type to "Trigger".  This will continuously detect collisions without causing
any physical reaction.
]]--

Script.enabled=true --bool "Start Enabled"
Script.show=false --bool "Show In-Game"
Script.Tipped=false

Script.NewRespawnPoint=nil --entity "Respawn Point"

function Script:Start()	
	WidgetVolume:Create(self.entity,self.show)
end

function Script:ShouldTrigger(entity)
	local entcollision = entity:GetCollisionType()
	if entcollision == Collision.Character then
		return true
	end
	
	return false
end

function Script:Collision(entity, position, normal, speed)
	if self.enabled then
		if self:ShouldTrigger(entity)==true then
			-- Keep the entity awake.
			entity:AddForce(0,0,0)
			if not self.Tipped then
				self:Trigger(entity)
			end	
		end
	end
end

function Script:Trigger(entity)
	if not self.firstTime then
		-- For the first time fire a special output
		self.component:CallOutputs("OnFirstTouch")
		self.firstTime = true 
	end
	
	-- Normal tick output
	self.component:CallOutputs("OnTrigger")
	--System:Print("OnTrigger")
		
	if entity:GetKeyValue("type") == "player" then
		if self.NewRespawnPoint ~= nil then
			entity.script:SetNewRespawnPoint(self.NewRespawnPoint)
		end
	end		

	self.Tipped=true
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