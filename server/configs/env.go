package configs

import (
	"github.com/MrMohebi/greenhouse-automation.git/common"
	"github.com/joho/godotenv"
	"os"
)

var IsInitOnce = false

func EnvSetup() {
	if !IsInitOnce {
		err := godotenv.Load()
		common.IsErr(err, true, "Error loading .env file")
		IsInitOnce = true
	} else {
		println("initialized envs once")
	}
}

func EnvMongoURI() string {
	return os.Getenv("MONGO_FINAL_URI")
}

func EvnMongoDB() string {
	return os.Getenv("MONGO_DB")
}
