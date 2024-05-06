extends Node

func _ready():
	# set up FMOD
	Fmod.set_software_format(0, Fmod.FMOD_SPEAKERMODE_STEREO)
	Fmod.init(1024, Fmod.FMOD_SPEAKERMODE_INIT_LIVEUPDATE, Fmod.FMOD_INIT_NORMAL)
	
	# load Banks
	Fmod.load_bank("res://sound/Desktop/Master.strings.bank", Fmod.FMOD_STUDIO_LOAD_BANK_NORMAL)
	Fmod.load_bank("res://sound/Desktop/Master.bank", Fmod.FMOD_STUDIO_LOAD_BANK_NORMAL)
	Fmod.load_bank("res://sound/Desktop/Ambients.bank", Fmod.FMOD_STUDIO_LOAD_BANK_NORMAL)
	Fmod.load_bank("res://sound/Desktop/Music.bank", Fmod.FMOD_STUDIO_LOAD_BANK_NORMAL)
	Fmod.load_bank("res://sound/Desktop/SFX.bank", Fmod.FMOD_STUDIO_LOAD_BANK_NORMAL)
	
	#register listener
	Fmod.add_listener(0, self)
	
	#Play test event
	Fmod.play_one_shot("event:/TEST_EVENT", self)
