import "Scripts/GameRules.lua"
import "Scripts/Objects/Pivots/WidgetSprite.lua"
import "Scripts/Objects/Volumes/WidgetVolume.lua"

--[[ 
Sandbox mode is by default enabled if you run the map from the editor.
However, sandbox mode is mandatory if you so wish to put your game/demo on the
Game Launcher. 

In the Game Launcher, your app (this app with the menu and all) will NOT be pushed 
to the workshop. So, what we do here is store the property to a value and then
use that to tell if this is from the editor/on the gamelauncher, or a stand-alone
play.
]]--
if System:GetProperty("sandbox")=="1" then SANDBOX = true else SANDBOX = false end

-- Developer property.
DEVELOPER = System:GetProperty("dev","0")

-- If debug, always put it in sandbox.
if DEBUG then
SANDBOX = true
end

--[[
Start map. The map that will play when the "New Game" button is pressed,
or what map you wish to launch on the game launcher.
--]]
local startmap = "Maps/start.map"

--[[ 
Initialize Steamworks (optional)
The app does not call Steamworks at all, leaving you to control if it's enabled 
or not in this script file. 
--]]
Steamworks:Initialize()

--[[ 
Here is where we do the magic!
If we are NOT under sandbox mode, we'll tell our app (Which is calling us normally)
to create the app class, which will then create more classes (menu, RWorld, etc)

If we are under sandbox mode, We just run modified stock lua code. 
--]]

--Set the application title
title="$PROJECT_TITLE"

if not SANDBOX then
	-- Tell the executable to create the App class!!
	local backgroundmap = "Maps/start.map"
	app = App:Create(title, backgroundmap)
	app:SetStartMap(startmap)
		
	--[[ 
	We loop the app here like this, and not in the app class in code so we can still
	communicate with the App class in other scripts.
	--]]
	while app:Loop() do
	end
else

	--Create a window
	local windowstyle = Window.Titlebar
	if System:GetProperty("fullscreen")=="1" then windowstyle=windowstyle+Window.FullScreen end
	window=Window:Create(title,0,0,System:GetProperty("screenwidth","1024"),System:GetProperty("screenheight","768"),windowstyle)
	window:HideMouse()

	--Create the graphics context
	context=Context:Create(window,0)
	if context==nil then return end

	--Create a world
	world=World:Create()
	world:SetLightQuality((System:GetProperty("lightquality","1")))

	-- Change the map
	function LoadMap(map)
		if map~= nil then
			changemapname = map
		else
			Systen:Print("Failed to load map!")
		end
	end	

	--Load a map
	local mapfile = System:GetProperty("map",startmap)
	if Map:Load(mapfile)==false then return end
	if mapfile~= nil then
		LoadMap(mapfile)
	else
		Error("Failed to load map!")
		return false 
	end	
		
	-- Loading screen
	-- DON'T TOUCH THESE PATHS UNLESS YOU EDITED THE SRC!!
	local loadingbackground = Texture:Load("Materials/UI/LoadingScreen/loadingscreen_default.tex")
	local loadingicon = Texture:Load("Materials/UI/LoadingScreen/loadingicon.tex")	
		
	--[[
	This mimics how the loading screen looks with our app.
	--]]
	function LoadingScreen()
		context:DrawImage(loadingbackground,0,0, window:GetWidth(), window:GetHeight())	
		local x = context:GetWidth() - loadingicon:GetWidth()
		local y = context:GetHeight() - loadingicon:GetHeight()
		context:DrawImage(loadingicon,x,y,loadingicon:GetWidth(),loadingicon:GetHeight() )	
		context:Sync(false)
	end		
		
	--[[
	Rather then waiting for a keypress, we have it a bool which a script 
	can set to true to end the program.
	
	Key presses with Escape and End will break the while loop.
	--]]
	while not SHUTDOWN do 
		
		--If window has been closed, end the program
		if window:Closed() then break end
		
		--Close the program when this bool is true.
		if window:KeyDown(Key.Escape) or window:KeyDown(Key.End) then break end	
		
		--Handle map change
		if changemapname~=nil then
			
			--Clear all entities
			world:Clear()
			
			--Load the next map
			Time:Pause()
			
			-- Load our precache script.
			Interpreter:ExecuteFile("Scripts/PrecacheGlobal.lua")
			if Map:Load(changemapname,"LoadingScreen")==false then return end
			Time:Resume()
			
			changemapname = nil
		end	
		
		--Update the app timing
		Time:Update()
		
		--Update the world
		world:Update()
		
		--Render the world
		world:Render()
			
		--Render statistics
		context:SetBlendMode(Blend.Alpha)
		if DEBUG then
			context:SetColor(1,0,0,1)
			context:DrawText("Debug Mode",2,2)
			context:SetColor(1,1,1,1)
			context:DrawStats(2,22)
			context:SetBlendMode(Blend.Solid)
		else
			--Toggle statistics on and off
			if (window:KeyHit(Key.F11)) then showstats = not showstats end
			if showstats then
				context:SetColor(1,1,1,1)
				context:DrawText("FPS: "..Math:Round(Time:UPS()),2,2)
			end
		end
		
		--Refresh the screen
		context:Sync(true)
	
	end
end