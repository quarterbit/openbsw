import qrcode

# Create QR code for the email
email = "Thomas.Fleischmann@accenture.com"
mailto_url = f"mailto:{email}"

# Create QR code
qr = qrcode.QRCode(
    version=1,
    error_correction=qrcode.constants.ERROR_CORRECT_L,
    box_size=10,
    border=4,
)

qr.add_data(mailto_url)
qr.make(fit=True)

# Create QR code image with transparent background
img = qr.make_image(fill_color="#663399", back_color="white")  # OpenBSW purple

# Save the QR code
img.save("/workspaces/openbsw/openbsw-site/images/email-qr-thomas.png")

print(f"QR code generated for: {email}")