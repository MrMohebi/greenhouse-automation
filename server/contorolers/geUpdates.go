package contorolers

import (
	"github.com/MrMohebi/greenhouse-automation.git/faces"
	"github.com/MrMohebi/greenhouse-automation.git/models"
	"github.com/gin-gonic/gin"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"net/http"
)

func GetUpdates() gin.HandlerFunc {
	return func(context *gin.Context) {
		context.JSON(http.StatusOK, faces.UpdatesRes{
			Repeats: []models.Repeat{},
			Triggers: []models.Trigger{
				{primitive.ObjectID{}, 13, "", "air conditioner", 0, 22.0, true, false, 0},
				{primitive.ObjectID{}, 14, "", "Humidifier", 70.0, 80.0, true, false, 0},
			},
		})
	}
}
