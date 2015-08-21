--[[
Purpose:  This script will make any entity act as a collision trigger.  It works best when you set the
entity's collision type to "Trigger".  This will continuously detect collisions without causing
any physical reaction.
]]--

Script.enabled=true --bool "Start Enabled"
Script.show=false --bool "Show In-Game"
Script.allowcharacters=true --bool "Allow Characters"
Script.allowprops=false --bool "Allow Props"
Script.material = nil
Script.entered = false
Script.exited = false
Script.hadCollision = false

Script.RefireTime = 1.0 -- float "Refire Time"
Script.Timer = 0
Script.Tipped=false

Script.destPoint = "" --entity "Teleport To"

function Script:Start()	
	WidgetVolume:Create(self.entity,self.show)
end

function Script:UpdatePhysics()
	if self.enabled then
		if self.entered then
			if self.hadCollision == false then
				if self.exited == false then
					self.exited = true
					self.component:CallOutputs("OnEndTouchAll")
					--System:Print("OnEndTouchAll")
					self.Timer = 0
					self.Tipped=false
					self.entered = false
				end
			end
		end
		self.hadCollision = false
	end	
end

function Script:Collision(entity, position, normal, speed)
	if self.enabled then
		if self:ShouldTrigger(entity)==true then
			self.hadCollision = true
			entity:AddForce(0,0,0)
			
			if self.entered == false then
				self.component:CallOutputs("OnStartTouch")
				--System:Print("OnStartTouch")
				
				self.entered = true
				self.exited = false
			end
			
			if not self.Tipped then
				self:Trigger(entity)
			end	
		end
	end	
end

function Script:UpdateWorld()
	if self.enabled and self.entered then
		-- A negitive value will disable this.
		if self.Tipped and self.RefireTime >= 0 then
			self.Timer = self.Timer + (Time:GetSpeed() /100)
			if self.Timer > self.RefireTime then
				self.Tipped = false
				self.Timer = 0
			end	
		end
	end	
end

function Script:Trigger(entity)
		self.component:CallOutputs("OnTriggerTick")
		--System:Print("OnTriggerTick")
		if self.destPoint ~= nil then
			local spawnPos = self.destPoint:GetPosition()
			local spawnRot = self.destPoint:GetRotation()
			
			entity:SetPosition(spawnPos)
			entity:SetRotation(spawnRot)
			
			-- If we are the player, apply the destination's rotation to the camera.
			if entity:GetKeyValue("type") == "player" then
				if entity.script ~= nil then
					if type(entity.script.SetCameraRotation)=="function" then
						entity.script:SetCameraRotation(spawnRot)
					end	
				end
			end
		end		
		
		self.Tipped=true
end

function Script:ShouldTrigger(entity)
	local entcollision = entity:GetCollisionType()
	
	if not self.allowcharacters then
		if entcollision == Collision.Character then
			return false
		end
	end
	
	if not self.allowprops then
		if entcollision == Collision.Prop or entcollision == Collision.PickedUpProp then
			return false
		end
	end	

	return true
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