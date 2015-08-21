--------------------------------------------------- 
--[[Weapon Slot Defines: Set Weapon Slots ]]--	
--------------------------------------------------- 
WpnSlot={}
WpnSlot.Melee = 1
WpnSlot.Pistol = 2
WpnSlot.Shotgun = 3
WpnSlot.Smg= 4
WpnSlot.M4 = 5
------------------------------------
--[[End of Weapon Slot Defines ]]--	
------------------------------------

--------------------------------------------------- 
--[[Collsion Defines: Make new Collision Rules ]]--	
--------------------------------------------------- 
Collision.CharacterBlocker = 9
Collision.PropBlocker = 10
Collision.PickInfo = 11
Collision.PickedUpProp = 12
Collision.Item = 13

-- Props can activate triggers.
Collision:SetResponse(Collision.Prop, Collision.Trigger, Collision.Trigger)	
	
-- CSG Collisions
Collision:SetResponse(Collision.CharacterBlocker, Collision.Character, Collision.Collide)
Collision:SetResponse(Collision.PropBlocker, Collision.Prop, Collision.Collide)
Collision:SetResponse(Collision.PropBlocker, Collision.PickedUpProp, Collision.Collide)	

-- Picked up objects can still collide with triggers, but never characters.
Collision:SetResponse(Collision.PickedUpProp, Collision.Character, Collision.None)
Collision:SetResponse(Collision.PickedUpProp, Collision.Scene, Collision.Collide)
Collision:SetResponse(Collision.PickedUpProp, Collision.Prop, Collision.Collide)
Collision:SetResponse(Collision.PickedUpProp, Collision.Trigger, Collision.Trigger)
Collision:SetResponse(Collision.PickedUpProp, Collision.PickedUpProp, Collision.None)
	
-- Items
Collision:SetResponse(Collision.Item, Collision.Character, Collision.Trigger)
Collision:SetResponse(Collision.Item, Collision.Scene, Collision.Collide)
Collision:SetResponse(Collision.Item, Collision.Prop, Collision.Collide)
Collision:SetResponse(Collision.Item, Collision.Trigger, Collision.Trigger)
Collision:SetResponse(Collision.Item, Collision.PickedUpProp, Collision.None)	
	
-- PickInfo
Collision:SetResponse(Collision.PickInfo, Collision.Scene, Collision.Collide)
Collision:SetResponse(Collision.PickInfo, Collision.Prop, Collision.Collide)
Collision:SetResponse(Collision.PickInfo, Collision.PickedUpProp, Collision.Collide)
Collision:SetResponse(Collision.PickInfo, Collision.Trigger, Collision.None)
Collision:SetResponse(Collision.PickInfo, Collision.Item, Collision.Collide)
---------------------------------
--[[End of Collsion Defines ]]--	
---------------------------------

--[[
Load models onto memory if you wish to "spawn" them later such as npcs, 
or gibs. It's best to do this at a Start function as loading a model in real time
causes a slow down. 
--]]
function PrecacheObject(obj)
	if obj == nil then return end
	local ext = FileSystem:ExtractExt(obj)
	if (ext == "mdl") or (ext == "pfb") then
		if (ext == "mdl") then
			local model = Model:Load(obj)
			model:Hide()
			System:Print("Precached model: " ..obj)
		elseif (ext == "pfb") then
			local prefab = Prefab:Load(obj)
			prefab:Hide()
			System:Print("Precached prefab: " ..obj)
		end
	end	
end