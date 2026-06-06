// ─── Classes ────────────────────────────────────────────────

class Client {
  constructor(name, id) {
    this.name = name;   // מחרוזת
    this.id   = id;     // מספר (תעודת זהות)
  }
}

class Car {
  constructor(model, year, color) {
    this.model      = model;   // מחרוזת
    this.year       = year;    // שנת ייצור (מספר)
    this.color      = color;   // מחרוזת
    this.complaints = [];      // מערך של מספרים
    this.value      = 0;       // מספר
    this.clients    = [];      // מערך של אובייקטי Client
  }

  addComplaint(code) {
    this.complaints.push(code);
  }

  addClient(client) {
    this.clients.push(client);
  }

  setComplaints(arr) {
    this.complaints = arr;
  }
}

// ─── Helpers ────────────────────────────────────────────────

function syntaxHighlight(obj) {
  const json = JSON.stringify(obj, null, 2);
  return json.replace(
    /("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g,
    match => {
      if (/^"/.test(match)) {
        if (/:$/.test(match)) return `<span class="json-key">${match}</span>`;
        return `<span class="json-str">${match}</span>`;
      }
      if (/true|false/.test(match)) return `<span class="json-bool">${match}</span>`;
      if (/null/.test(match))       return `<span class="json-null">${match}</span>`;
      return `<span class="json-num">${match}</span>`;
    }
  );
}

// ─── Load JSON and render ────────────────────────────────────

fetch('myCar.json')
  .then(res => res.json())
  .then(data => {
    // Build Car object from JSON
    const car = new Car(data.model, data.year, data.color);
    car.setComplaints(data.complaints);
    car.value = data.value;

    // Build Client objects from JSON
    data.clients.forEach(c => {
      car.addClient(new Client(c.name, c.id));
    });

    render(car, data);
  });

function render(car, rawJson) {
  const app = document.getElementById('app');

  // Card 1 — Car details
  app.innerHTML += `
    <div class="card">
      <div class="card-title">פרטי הרכב — Car Object</div>
      <div class="car-grid">
        <div class="car-field"><label>מודל</label><span>${car.model}</span></div>
        <div class="car-field"><label>שנת ייצור</label><span>${car.year}</span></div>
        <div class="car-field"><label>צבע</label><span>${car.color}</span></div>
      </div>

      <div class="divider"></div>

      <div class="car-field" style="background:transparent;padding:0">
        <label>ערך הרכב</label>
        <div class="value-display">₪${car.value.toLocaleString('he-IL')}</div>
        <div class="value-note">מחיר שוק נוכחי</div>
      </div>

      <div class="divider"></div>

      <div class="card-title" style="margin-bottom:10px">קודי תקלות</div>
      <div class="complaints-row">
        ${car.complaints.map(c => `<span class="badge">#${c}</span>`).join('')}
      </div>
    </div>
  `;

  // Card 2 — Clients
  app.innerHTML += `
    <div class="card">
      <div class="card-title">לקוחות ששכרו את הרכב — Client Objects</div>
      <div class="client-list">
        ${car.clients.map(c => `
          <div class="client-card">
            <div class="client-avatar">${c.name[0]}</div>
            <div class="client-info">
              <p>${c.name}</p>
              <p>ת.ז. ${c.id}</p>
            </div>
          </div>
        `).join('')}
      </div>
    </div>
  `;

  // Card 3 — JSON source
  app.innerHTML += `
    <div class="card">
      <div class="card-title">אובייקט myCar — JSON</div>
      <div class="json-block">${syntaxHighlight(rawJson)}</div>
    </div>
  `;
}