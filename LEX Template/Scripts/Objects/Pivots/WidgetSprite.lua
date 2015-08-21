if WidgetSprite~=nil then return end
WidgetSprite={}
WidgetSprite.entity = nil

function WidgetSprite:Create(entity)
	if entity==nil then Debug:Error("Entity cannot be nil.") end
	self.entity = entity
	material = Material:Load("Materials/Effects/Invisible.mat")
	self.entity:SetMaterial(material)
	material:Release()
end