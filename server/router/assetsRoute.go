package router

import (
	"github.com/gin-gonic/gin"
)

func AssetsRoute(r *gin.Engine) {
	// docs assets
	r.StaticFile("/docs/redoc.standalone.js", "./templates/doc/redoc.standalone.js")
	r.StaticFile("/docs/apiDoc.yaml", "./templates/doc/apiDoc.yaml")
}
