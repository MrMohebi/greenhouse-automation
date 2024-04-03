package contorolers

import (
	"github.com/gin-gonic/gin"
	"net/http"
)

func Index() gin.HandlerFunc {
	return func(context *gin.Context) {
		context.HTML(http.StatusOK, "index.html", nil)
	}
}
