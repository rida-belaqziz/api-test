from django.db import models



# Create the model
class Seat(models.Model):
    seat_number = models.CharField(max_length=10, unique=True)
    is_occupied = models.BooleanField(default=False)

    def __str__(self):
        return f'Seat {self.seat_number} - {"Occupied" if self.is_occupied else "Available"}'