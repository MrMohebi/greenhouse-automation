package faces

import "github.com/MrMohebi/greenhouse-automation.git/models"

type UpdatesRes struct {
	Repeats  []models.Repeat
	Triggers []models.Trigger
}
