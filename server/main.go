package main

import (
	"github.com/MrMohebi/greenhouse-automation.git/common"
	"github.com/MrMohebi/greenhouse-automation.git/configs"
	"github.com/MrMohebi/greenhouse-automation.git/router"
	"github.com/gin-gonic/gin"
)

// nodemon --exec go run main.go --signal SIGTERM

func main() {
	configs.Setup()

	server := gin.Default()

	router.Routs(server)

	err := server.Run("localhost:8005")
	common.IsErr(err, true, "Err in starting server")
}
