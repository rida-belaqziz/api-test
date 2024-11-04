from django.shortcuts import render

# Create your views here.
from rest_framework.decorators import api_view
from rest_framework.response import Response
from .models import Seat
from rest_framework import status

@api_view(['GET'])
def get_seats(request):
    seats = Seat.objects.all()
    seat_data = [{"seat_number": seat.seat_number, "is_occupied": seat.is_occupied} for seat in seats]
    return Response(seat_data)

@api_view(['POST'])
def add_seat(request):
    seat_number = request.data.get("seat_number")
    if not seat_number:
        return Response({"error": "Seat number is required"}, status=status.HTTP_400_BAD_REQUEST)
    
    seat, created = Seat.objects.get_or_create(seat_number=seat_number)
    if not created:
        return Response({"error": "Seat already exists"}, status=status.HTTP_400_BAD_REQUEST)

    return Response({"message": "Seat added successfully"})

@api_view(['POST'])
def update_seat_status(request):
    seat_number = request.data.get("seat_number")
    is_occupied = request.data.get("is_occupied")

    try:
        seat = Seat.objects.get(seat_number=seat_number)
        seat.is_occupied = is_occupied
        seat.save()
        return Response({"message": f"Seat {seat_number} updated successfully"})
    except Seat.DoesNotExist:
        return Response({"error": "Seat not found"}, status=status.HTTP_404_NOT_FOUND)