# Stage 1: build the static site
FROM python:3.12-slim AS builder

WORKDIR /build

RUN pip install --no-cache-dir mkdocs-material==9.6.11

COPY .mkdocs.yml .
COPY docs/ docs/

RUN mkdocs build -f .mkdocs.yml -d /build/site

# Stage 2: serve with nginx
FROM nginx:alpine AS server

COPY --from=builder /build/site /usr/share/nginx/html

# Clean URLs: remove .html extension from links
COPY nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE 80
