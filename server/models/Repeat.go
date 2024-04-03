package models

import (
	"go.mongodb.org/mongo-driver/bson/primitive"
)

type Repeat struct {
	Id           primitive.ObjectID `json:"id" bson:"_id"`
	PinNum       int                `json:"pinNum" validate:"required"`
	VarName      string             `json:"varName" validate:"required"`
	Name         string             `json:"name" validate:"required"`
	Each         int                `json:"each" validate:"required"`
	Duration     int                `json:"duration" validate:"required"`
	ActiveState  bool               `json:"activeState" validate:"required"`
	DefaultState bool               `json:"defaultState" validate:"required"`

	CreatedAt int32 `json:"createdAt" validate:"required"`
}

//var RepeatsCollection *mongo.Collection = configs.GetCollection(configs.GetDBClint(), "Repeats")
