FROM golang:1.20-alpine as builder
RUN apk update && apk upgrade && apk add --no-cache bash git openssh
WORKDIR /app
COPY go.mod go.sum ./
RUN go mod download
COPY . .
RUN go build -o main .


FROM alpine:3.17
COPY --from=builder /app/main /
COPY --from=builder /app/config.ini /
COPY --from=builder /app/.env /
COPY templates /templates
CMD ["./main"]
