--[[
Purpose: A simple script that spawns prefabs at a objects's location and rotation.
--]]

Script.SpawnOnStart=false --bool "Spawn on Start"
Script.SpawnObject = "" --path "Prefab To Spawn" "Prefab (*.pfb):pfb|Prefabs"
Script.Force=Vec3(0,0,0) --Vec3 "Prefab Force"

function Script:Start()
	WidgetSprite:Create(self.entity)
	PrecacheObject(self.SpawnObject)
	if self.SpawnOnStart then
		self:Spawn()
	end	
end

--Spawn Object
function Script:Spawn()
	if self.SpawnObject~="" then
		local prefab = Prefab:Load(self.SpawnObject)
		if prefab~=nil then
			if prefab.script~=nil then
				-- Get OUR Pos and Rot and apply it to the prefab.
				prefab:SetPosition(self.entity:GetPosition())
				prefab:SetRotation(self.entity:GetRotation())
				prefab:SetVelocity(self.Force)
				-- Keep the flow, and fire an output.
				--System:Print("PrefabSpawner.lua: Spawning!")
				self.component:CallOutputs("OnSpawnPrefab")
			else
				prefab:Release()
			end
		end
	end	
	
end

-- The input
function Script:SpawnPrefab()--in
	self:Spawn()
end