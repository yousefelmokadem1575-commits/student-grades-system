# Aeris Platform

React frontend + FastAPI backend (weather + NASA POWER climate risk).

## Run
Backend (terminal 1):
    cd backend
    python -m venv venv && source venv/bin/activate   # Windows: venv\Scripts\activate
    pip install -r requirements.txt
    uvicorn main:app --reload --port 8000              # docs: http://localhost:8000/docs

Frontend (terminal 2):
    cd frontend
    npm install
    npm run dev                                        # http://localhost:5173

Optional: copy backend/.env.example to .env and frontend/.env.example to .env.

## Backend endpoints
GET /api/health
GET /api/geocode/search?q=&lang=en|ar
GET /api/geocode/{id}
GET /api/weather?lat=&lon=
GET /api/weather/current-many?points=lat,lon;lat,lon
GET /api/air-quality?lat=&lon=
GET /api/radar-tiles
GET /api/climate-risk?lat=&lon=&date_str=YYYY-MM-DD&event_type=   (your original endpoint, same response + risk_label_en)

## Tests
    cd backend && python -m pytest -q tests
