package contorolers

import (
	"github.com/gin-gonic/gin"
	"net/http"
)

func Docs() gin.HandlerFunc {
	return func(context *gin.Context) {
		context.HTML(http.StatusOK, "docs.html", nil)
	}
}
