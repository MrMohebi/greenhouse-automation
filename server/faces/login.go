package faces

type LoginRes struct {
	Token string `json:"token"`
}

type LoginReq struct {
	Username string `json:"username" form:"username" validate:"required"`
	Password string `json:"password" form:"password" validate:"required"`
}
