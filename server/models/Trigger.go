package models

import (
	"go.mongodb.org/mongo-driver/bson/primitive"
)

type Trigger struct {
	Id           primitive.ObjectID `json:"id" bson:"_id"`
	PinNum       int                `json:"pinNum" validate:"required"`
	VarName      string             `json:"varName" validate:"required"`
	Name         string             `json:"name" validate:"required"`
	Min          float32            `json:"min" validate:"required"`
	Max          float32            `json:"max" validate:"required"`
	ActiveState  bool               `json:"activeState" validate:"required"`
	DefaultState bool               `json:"defaultState" validate:"required"`

	CreatedAt int32 `json:"createdAt" validate:"required"`
}

//var TriggersCollection *mongo.Collection = configs.GetCollection(configs.GetDBClint(), "triggers")
