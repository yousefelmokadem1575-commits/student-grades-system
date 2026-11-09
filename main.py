"""Aeris Weather API: weather proxy (Open-Meteo) + NASA POWER climate risk, one backend for the React app.
Run:  uvicorn main:app --reload --port 8000     Docs: http://localhost:8000/docs"""
import os
from contextlib import asynccontextmanager
import httpx
from fastapi import FastAPI, HTTPException, Query
from fastapi.middleware.cors import CORSMiddleware
from services import http, nasa, openmeteo

@asynccontextmanager
async def lifespan(_: FastAPI):
    http.client = httpx.AsyncClient(timeout=12.0, headers={"User-Agent": "aeris-weather/2.0"})
    yield
    await http.client.aclose()

app = FastAPI(title="Aeris Weather & NASA Climate Risk API", version="2.0", lifespan=lifespan)
origins = [o.strip() for o in os.getenv("CORS_ORIGINS", "*").split(",") if o.strip()]
app.add_middleware(CORSMiddleware, allow_origins=origins, allow_credentials=False, allow_methods=["GET"], allow_headers=["*"])

LAT = Query(..., ge=-90, le=90)
LON = Query(..., ge=-180, le=180)

@app.get("/api/health")
async def health():
    return {"status": "ok"}

@app.get("/api/geocode/search")
async def geocode_search(q: str = Query(..., min_length=2, max_length=80), lang: str = Query("en", pattern="^(en|ar)$")):
    return await openmeteo.search(q.strip(), lang)

@app.get("/api/geocode/{place_id}")
async def geocode_get(place_id: int):
    return await openmeteo.get_place(place_id)

@app.get("/api/weather")
async def weather(lat: float = LAT, lon: float = LON):
    return await openmeteo.forecast(lat, lon)

@app.get("/api/weather/current-many")
async def weather_current_many(points: str = Query(..., description="lat,lon;lat,lon (max 20)")):
    try:
        pts = [tuple(float(x) for x in p.split(",")) for p in points.split(";") if p]
        assert 0 < len(pts) <= 20 and all(len(p) == 2 and -90 <= p[0] <= 90 and -180 <= p[1] <= 180 for p in pts)
    except (ValueError, AssertionError):
        raise HTTPException(400, "points must look like 'lat,lon;lat,lon' (max 20)")
    return await openmeteo.current_many(pts)

@app.get("/api/air-quality")
async def air_quality(lat: float = LAT, lon: float = LON):
    return await openmeteo.air_quality(lat, lon)

@app.get("/api/radar-tiles")
async def radar_tiles():
    return await openmeteo.radar_tiles()

@app.get("/api/climate-risk")
async def get_climate_risk(lat: float = LAT, lon: float = LON, date_str: str = Query(...), event_type: str = "general"):
    return await nasa.climate_risk(lat, lon, date_str, event_type)
