if WidgetVolume~=nil then return end
WidgetVolume={}
WidgetVolume.entity=nil

function WidgetVolume:Create(entity,show)
	if entity==nil then Debug:Error("Entity cannot be nil.") end
	self.entity=entity
	
	if not show then
		material = Material:Load("Materials/Effects/Invisible.mat")
		self.entity:SetMaterial(material)
		material:Release()
	end	

	self.entity:SetCollisionType(Collision.Trigger)	
end