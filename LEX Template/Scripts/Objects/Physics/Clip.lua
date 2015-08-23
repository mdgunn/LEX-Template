--[[
Purpose: Used with Developer/Clip.mat. use this script to control collision rules
on brushes. These "invisible walls" can be turned on and off unlike collapsed 
geometry. 
]]--

Script.enabled=true --bool "Start Enabled"
Script.clipmode=0 --choice "Clip Type" "Block Characters,Block Props,Both"
Script.material = nil

function Script:Start()

	if self.enabled then
		if self.clipmode==0 then
			--Block only players
			self.savedclip = Collision.CharacterBlocker 
		elseif self.clipmode==1 then
			--Block only props
			self.savedclip = Collision.PropBlocker
		elseif self.clipmode==2 then
			--[[ Block both. Again, only use this option if you
			plan on toggling the clip.--]]
			self.savedclip = Collision.Scene
		end
		
		if self.savedclip ~= nil then
			self.entity:SetCollisionType(self.savedclip)
		end
	end
	
	-- Apply this to Developer/Clip.mat so you can see where
	-- all your clips are. This right here will make it invisible in-game.
	material = Material:Load("Materials/Effects/Invisible.mat")
	self.entity:SetMaterial(material)
end

function Script:Enable()--in
	if self.enabled==false then
		self.enabled=true
		self.entity:SetCollisionType(self.savedclip)
		self:CallOutputs("Enable")
	end
end

function Script:Disable()--in
	if self.enabled then
		self.enabled=false
		self.entity:SetCollisionType(Collision.None)
		self:CallOutputs("Disable")
	end
end