package router

import (
	"github.com/MrMohebi/greenhouse-automation.git/contorolers"
	"github.com/gin-gonic/gin"
)

func Routs(r *gin.Engine) {
	AssetsRoute(r)
	r.LoadHTMLGlob("templates/**/*.html")

	r.GET("/", contorolers.Index())
	r.GET("/docs", contorolers.Docs())

	r.GET("/getUpdates", contorolers.GetUpdates())

}
